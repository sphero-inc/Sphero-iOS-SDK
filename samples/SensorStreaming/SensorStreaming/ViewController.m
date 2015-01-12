//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>

@interface ViewController()

@property (nonatomic, strong) IBOutlet UILabel *xValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *yValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *zValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *pitchValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *rollValueLabel;
@property (nonatomic, strong) IBOutlet UILabel *yawValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *q0ValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *q1ValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *q2ValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *q3ValueLabel;

@property (strong, nonatomic) RKConvenienceRobot *robot;

@end

@implementation ViewController

- (void)viewDidLoad {
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
    [[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
}

- (void)appWillResignActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent stopDiscovery];
    [RKRobotDiscoveryAgent disconnectAll];
}

- (void)appDidBecomeActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent startDiscovery];
}

- (void)sendSetDataStreamingCommand {
	// Requesting the Accelerometer X, Y, and Z filtered (in Gs)
	//            the IMU Angles roll, pitch, and yaw (in degrees)
	//            the Quaternion data q0, q1, q2, and q3 (in 1/10000) of a Q
	RKDataStreamingMask mask =  RKDataStreamingMaskAccelerometerFilteredAll |
	RKDataStreamingMaskIMUAnglesFilteredAll   |
	RKDataStreamingMaskQuaternionAll;
	[_robot enableSensors:mask atStreamingRate:10];
}

- (void)handleAsyncMessage:(RKAsyncMessage *)message forRobot:(id<RKRobotBase>)robot {
	// Need to check which type of async data is received as this method will be called for
	// data streaming packets and sleep notification packets. We are going to ingnore the sleep
	// notifications.
	if ([message isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
		
		// Received sensor data, so display it to the user.
		RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)message;
		RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
		RKAccelerometerData *accelerometerData = sensorsData.accelerometerData;
		RKAttitudeData *attitudeData = sensorsData.attitudeData;
		RKQuaternionData *quaternionData = sensorsData.quaternionData;
		
		// Print data to the text fields
		_xValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.x];
		_yValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.y];
		_zValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.z];
		_pitchValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.pitch];
		_rollValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.roll];
		_yawValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.yaw];
		_q0ValueLabel.text = [NSString stringWithFormat:@"%.6f", quaternionData.quaternions.q0];
		_q1ValueLabel.text = [NSString stringWithFormat:@"%.6f", quaternionData.quaternions.q1];
		_q2ValueLabel.text = [NSString stringWithFormat:@"%.6f", quaternionData.quaternions.q2];
		_q3ValueLabel.text = [NSString stringWithFormat:@"%.6f", quaternionData.quaternions.q3];
	}
}

- (void)handleRobotStateChangeNotification:(RKRobotChangedStateNotification*)n {
    switch(n.type) {
        case RKRobotConnecting:
            [self handleConnecting];
            break;
        case RKRobotOnline: {
            // Do not allow the robot to connect if the application is not running
            RKConvenienceRobot *convenience = [RKConvenienceRobot convenienceWithRobot:n.robot];
            if ([[UIApplication sharedApplication] applicationState] != UIApplicationStateActive) {
                [convenience disconnect];
                return;
            }
            self.robot = convenience;
            [self handleConnected];
            break;
        }
        case RKRobotDisconnected:
            [self handleDisconnected];
            self.robot = nil;
            [RKRobotDiscoveryAgent startDiscovery];
            break;
        case RKRobotFailedConnect:
            // edge case - handle as you will.
            break;
    }
}

- (void)handleConnecting {
    // Handle robot connecting here
}

- (void)handleConnected {
    [_robot enableStablilization:NO];
    [_robot addResponseObserver:self];
    [self sendSetDataStreamingCommand];
}

- (void)handleDisconnected {
    // Handle robot disconnected here
}

@end
