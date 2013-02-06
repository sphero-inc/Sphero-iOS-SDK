//
//  ViewController.m
//  Locator
//
//  Created by Michael DePhillips on 7/12/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController

@synthesize textFieldNewX;
@synthesize textFieldNewY;
@synthesize textFieldNewYaw;
@synthesize flagSwitch;
@synthesize xValueLabel;
@synthesize yValueLabel;
@synthesize xVelocityValueLabel;
@synthesize yVelocityValueLabel;

-(void)dealloc {
    [textFieldNewX release];
    [textFieldNewY release];
    [textFieldNewYaw release];
    [flagSwitch release];
    [xValueLabel release];
    [yValueLabel release];
    [xVelocityValueLabel release];
    [yVelocityValueLabel release];
    [super dealloc];
}

-(void)viewDidLoad {
    [super viewDidLoad];
    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;

    calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    self.textFieldNewX = nil;
    self.textFieldNewY = nil;
    self.textFieldNewYaw = nil;
    self.flagSwitch = nil;
    self.xValueLabel = nil;
    self.yValueLabel = nil;
    self.xVelocityValueLabel = nil;
    self.yVelocityValueLabel = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
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
    
    // Stop rolling if it is
    [RKRollCommand sendStop];
    
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
        // Register for asynchronise data streaming packets
        [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleAsyncData:)];
        /* Start locator streaming */
        [self startLocatorStreaming];
    }
    robotOnline = YES;
}

-(void)startLocatorStreaming {
    
    // Note: If your ball has Firmware < 1.20 then these Quaternions
    //       will simply show up as zeros.
    
    // Sphero samples this data at 400 Hz.  The divisor sets the sample
    // rate you want it to store frames of data.  In this case 400Hz/40 = 10Hz
    uint16_t divisor = 20;
    
    // Packet frames is the number of frames Sphero will store before it sends
    // an async data packet to the iOS device
    uint16_t packetFrames = 1;
    
    // Count is the number of async data packets Sphero will send you before
    // it stops.  A count of 0, implements infinite data streaming at an SDK level.
    uint8_t count = 0;
    
    // Register for Locator X,Y position, and X,Y velocity
    RKDataStreamingMask sensorMask = RKDataStreamingMaskLocatorAll;
     
    //// Start data streaming for the locator data. The update rate is set to 20Hz with
    //// one sample per update, so the sample rate is 10Hz. Packets are sent continuosly.
    [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:divisor 
                                                   packetFrames:packetFrames
                                                     sensorMask:sensorMask 
                                                    packetCount:count];
}

- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
{
    // Need to check which type of async data is received as this method will be called for 
    // data streaming packets and sleep notification packets. We are going to ingnore the sleep
    // notifications.
    if ([asyncData isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        
        // Grab specific sensor data objects from the main sensor object
        RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)asyncData;
        RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
        RKLocatorData *locatorData = sensorsData.locatorData;
        
        // Print Locator Values
        self.xValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.position.x, @"cm"];
        self.yValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.position.y, @"cm"];
        self.xVelocityValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.velocity.x, @"cm/s"];
        self.yVelocityValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.velocity.y, @"cm/s"];
    }
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    }
}

-(IBAction)configurePressed:(id)sender {
    
    NSString *feildText = nil;
    int16_t newX = 0;
    int16_t newY = 0;
    int16_t newYaw = 0;
    
    // Get the values of the text fields
    feildText = self.textFieldNewX.text;
    if ([feildText length] > 0) {
        newX = [feildText integerValue];
    }
    feildText = self.textFieldNewY.text;
    if ([feildText length] > 0) {
        newY = [feildText integerValue];
    }
    feildText = self.textFieldNewYaw.text;
    if ([feildText length] > 0) {
        newYaw = [feildText integerValue];
    }
    
    // Convert the value of the toggle switch to the configure locator flag
    RKConfigureLocatorFlag flag = (flagSwitch.isOn ? RKConfigureLocatorRotateWithCalibrateFlagOn : RKConfigureLocatorRotateWithCalibrateFlagOff );
    
    // Send command to configure locactor
    // After sending the command, you should see the x and y values of the labels
    // change to the ones you specified in the text fields
    [RKConfigureLocatorCommand sendCommandForFlag:flag newX:newX newY:newY newYaw:newYaw];
}

-(IBAction)upPressed:(id)sender {
    [RKRollCommand sendCommandWithHeading:0 velocity:0.6];
}

-(IBAction)downPressed:(id)sender {
    [RKRollCommand sendCommandWithHeading:180 velocity:0.6];
}

-(IBAction)leftPressed:(id)sender {
    [RKRollCommand sendCommandWithHeading:270 velocity:0.6];
}

-(IBAction)rightPressed:(id)sender {
    [RKRollCommand sendCommandWithHeading:90 velocity:0.6];
}

-(IBAction)stopPressed:(id)sender {
    [RKRollCommand sendStop];
}

// Dismiss keyboard when view is tapped
-(IBAction)dismissKeyboard:(id)sender {
    
    [textFieldNewX resignFirstResponder];
    [textFieldNewY resignFirstResponder];
    [textFieldNewYaw resignFirstResponder];
}

@end
