//
//  ViewController.m
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"

#define DEGREES_TO_RADIANS(angle) (angle / 180.0 * M_PI)

@implementation ViewController
@synthesize randomMain, sphero, targetSpheroLoc;
@synthesize yawLabel, accelyLabel, accelxLabel;


//View Handelers
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(applicationWillTerminate:) name:UIApplicationWillTerminateNotification object:nil];
    
    //SpaceFighter
    targetSpheroLoc = sphero.center;

    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
    
    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
    

}

- (void)viewDidUnload
{
    [super viewDidUnload];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [self animateSphero];
    
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];    
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation 
{
    if (interfaceOrientation==UIInterfaceOrientationLandscapeLeft || interfaceOrientation==UIInterfaceOrientationLandscapeRight)
        return YES;
    
    return NO;
}

//When Application closes, return Sphero to normal state.
- (void)applicationWillTerminate:(NSNotification *)notifaction
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appWillResignActive:(NSNotification*)notification {

    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}


//////////////////
//Sphero
/////////////////

//Set up Sphero for Gameplay

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    //Give Command  here to Turn off stability and turn on Sphero Streaming

    if(!robotOnline) {
        [RKBackLEDOutputCommand sendCommandWithBrightness:1.0];
        [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:1.0 blue:1.0];
        [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOff];
        
        // Request Data Streaming
        [self sendSetDataStreamingCommand];

        ////Register for asynchronise data streaming packets
        [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleDataStreaming:)];
        
        
    }
    robotOnline = YES;
}


///////////////////////////////
//SpheroStreaming
///////////////////////////////

-(void)sendSetDataStreamingCommand {
    
    // Requesting the Accelerometer X, Y, and Z filtered (in Gs)
    //            the IMU Angles yaw
    RKDataStreamingMask mask =  RKDataStreamingMaskAccelerometerFilteredAll |
                                RKDataStreamingMaskIMUYawAngleFiltered;
    
    // Note: If your ball has Firmware < 1.20 then these Quaternions
    //       will simply show up as zeros.
    
    // Sphero samples this data at 400 Hz.  The divisor sets the sample
    // rate you want it to store frames of data.  In this case 400Hz/40 = 10Hz
    uint16_t divisor = 20;
    
    // Packet frames is the number of frames Sphero will store before it sends
    // an async data packet to the iOS device
    uint16_t packetFrames = 1;
    
    // Count is the number of async data packets Sphero will send you before
    // it stops. 0 will register for infinite data streaming.
    uint8_t count = 0;
    
    // Send command to Sphero
    [RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:divisor
                                                   packetFrames:packetFrames
                                                     sensorMask:mask
                                                    packetCount:count];
    
}


-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    
    [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    
}


#pragma mark-SPHERO SENSOR STREAMING CODE

//Observer method that will be called as sensor data arrives from Sphero
- (void)handleDataStreaming:(RKDeviceAsyncData *)data
{
    //NSLog(@"handleDataStreaming: data - %@", data);
    
    if ([data isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        RKDeviceSensorsAsyncData *sensors_data = (RKDeviceSensorsAsyncData *)data;
        
        for (RKDeviceSensorsData *data in sensors_data.dataFrames) {
            RKAccelerometerData *accelerometer_data = data.accelerometerData;
            RKAttitudeData *attitude_data = data.attitudeData;
            
            //Accelerometer & Yaw Values Floats
            float yaw = attitude_data.yaw;
            yawLabel.text = [NSString stringWithFormat:@"%.f", (yaw)];
            
            // call method to rotate image for yaw value
            [self rotateImage:sphero degrees:-yaw];
            
            float y = accelerometer_data.acceleration.y + 1.0;
            if(y < 0.0) y = 0.0;
            if(y > 2.0) y = 2.0;
            y = y * 0.5;
            accelyLabel.text = [NSString stringWithFormat:@"%1.2f", (y)];
            
            float x = accelerometer_data.acceleration.x;
            y = accelerometer_data.acceleration.y * -1.0;
            float xOffset = x * 20.0;
            float yOffset = y * 20.0;
            accelxLabel.text = [NSString stringWithFormat:@"%1.2f", (x)];
            
            
            //Places Sphero's center
            CGPoint newCenter = CGPointMake(sphero.center.x + xOffset, sphero.center.y + yOffset);

            //PlaceSphero Back in center
            //Creates a boundry around the frame of the Phone so you can't lose him.
            if(newCenter.x < 0.0) newCenter.x = 0.0;
            if(newCenter.x > self.view.frame.size.height) newCenter.x = self.view.frame.size.height;
            if(newCenter.y < 0.0) newCenter.y = 0.0;
            if(newCenter.y > self.view.frame.size.width) newCenter.y = self.view.frame.size.width;
            
            targetSpheroLoc = newCenter;
        }
    }
}


//Animate Sphero

//Make Linear movements for Sphero's Image View

-(void)animateSphero {
    [UIView animateWithDuration:0.06
                          delay:0.0
                        options:UIViewAnimationCurveLinear 
                     animations:^{
                         sphero.center = targetSpheroLoc;
                     }
                     completion:^(BOOL finished) {
                         [self animateSphero];
                     }];
}

// method to rotate
-(void) rotateImage:(UIImageView *) imageView degrees:(CGFloat) degrees
{
    CGAffineTransform transform = CGAffineTransformMakeRotation(DEGREES_TO_RADIANS(degrees));
    imageView.transform = transform;
}


@end
