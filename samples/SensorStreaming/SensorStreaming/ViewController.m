//
//  ViewController.m
//  SensorStreaming
//
//  Created by Brian Smith on 03/28/12.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"

#import "RobotKit/RobotKit.h"

@implementation ViewController

@synthesize xValueLabel;
@synthesize yValueLabel;
@synthesize zValueLabel;
@synthesize pitchValueLabel;
@synthesize rollValueLabel;
@synthesize yawValueLabel;

- (void)dealloc
{
    [xValueLabel release];
    [yValueLabel release];
    [zValueLabel release];
    [pitchValueLabel release];
    [rollValueLabel release];
    [yawValueLabel release];
    [super dealloc];
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(appDidBecomeActive:) 
                                                 name:UIApplicationDidBecomeActiveNotification 
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(appWillResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    self.xValueLabel = nil;
    self.yValueLabel = nil;
    self.zValueLabel = nil;
    self.pitchValueLabel = nil;
    self.rollValueLabel = nil;
    self.yawValueLabel = nil;
    
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

-(void)appWillResignActive:(NSNotification*)notification {
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    
    // Turn off data streaming
    [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:0 
                                                   packetFrames:0 
                                                     sensorMask:RKDataStreamingMaskOff 
                                                    packetCount:0];
    // Unregister for async data packets
    [[RKDeviceMessenger sharedMessenger] removeDataStreamingObserver:self];
    
    // Restore stabilization (the control unit)
    [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOn];
    
    // Close the connection
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
    
    robotOnline = NO;
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
        // Start streaming sensor data
        ////First turn off stabilization so the drive mechanism does not move.
        [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOff];
        
        ////Register for asynchronise data streaming packets
        [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleAsyncData:)];
        
        //// Start data streaming for the accelerometer and IMU data. The update rate is set to 20Hz with
        //// one sample per update, so the sample rate is 10Hz. Packets are sent continuosly.
        [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:40 packetFrames:1 
                                                         sensorMask:RKDataStreamingMaskAccelerometerXFiltered |
                                                        RKDataStreamingMaskAccelerometerYFiltered |
                                                        RKDataStreamingMaskAccelerometerZFiltered |
                                                        RKDataStreamingMaskIMUPitchAngleFiltered |
                                                        RKDataStreamingMaskIMURollAngleFiltered |
                                                        RKDataStreamingMaskIMUYawAngleFiltered
                                                        packetCount:0];
    }
    robotOnline = YES;
}

- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
{
    // Need to check which type of async data is received as this method will be called for 
    // data streaming packets and sleep notification packets. We are going to ingnore the sleep
    // notifications.
    if ([asyncData isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        // Received sensor data, so display it to the user.
        RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)asyncData;
        RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
        RKAccelerometerData *accelerometerData = sensorsData.accelerometerData;
        RKAttitudeData *attitudeData = sensorsData.attitudeData;
        
        self.xValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.x];
        self.yValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.y];
        self.zValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.z];
        self.pitchValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.pitch];
        self.rollValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.roll];
        self.yawValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.yaw];
        
    }
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    }
}

@end
