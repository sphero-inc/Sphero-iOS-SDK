//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>

#define DEGREES_TO_RADIANS(angle) (angle / 180.0 * M_PI)

@interface ViewController()

@property (strong, nonatomic) RKConvenienceRobot* robot;

@property (strong, nonatomic) IBOutlet UILabel* yawLabel;
@property (strong, nonatomic) IBOutlet UILabel* accelxLabel;
@property (strong, nonatomic) IBOutlet UILabel* accelyLabel;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *spheroCenterHorizontal;
@property (strong, nonatomic) IBOutlet NSLayoutConstraint *spheroCenterVertical;
@property (strong, nonatomic) IBOutlet UIImageView *spheroImage;

@end

@implementation ViewController

#pragma mark - View lifecycle

- (void)viewDidLoad{
    [super viewDidLoad];

	/*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
    [[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
}

-(void)appWillResignActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent stopDiscovery];
    [RKRobotDiscoveryAgent disconnectAll];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent startDiscovery];
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
    [_robot setBackLEDBrightness:1.0f];
    [_robot setLEDWithRed:1.0f green:1.0f blue:1.0f];
    [_robot enableStablilization:NO];
    
    // Request Data Streaming
    [self sendSetDataStreamingCommand];
    [_robot.robot addResponseObserver:self];
}

- (void)handleDisconnected {
    [_robot.robot removeResponseObserver:self];
}

-(void)sendSetDataStreamingCommand {
    // Requesting the Accelerometer X, Y, and Z filtered (in Gs) the IMU Angles yaw
    RKDataStreamingMask mask =  RKDataStreamingMaskAccelerometerFilteredAll |
                                RKDataStreamingMaskIMUYawAngleFiltered;
	
    [_robot enableSensors:mask atStreamingRate:20];
}

-(void) handleAsyncMessage:(RKAsyncMessage*) data forRobot:(id<RKRobotBase>) robot{
    if ([data isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        RKDeviceSensorsAsyncData *sensors_data = (RKDeviceSensorsAsyncData *)data;
        
        for (RKDeviceSensorsData *data in sensors_data.dataFrames) {
            RKAccelerometerData *accelerometer_data = data.accelerometerData;
            RKAttitudeData *attitude_data = data.attitudeData;
            
            //Accelerometer & Yaw Values Floats
            float yaw = attitude_data.yaw;
            _yawLabel.text = [NSString stringWithFormat:@"%.f", (yaw)];
            
            // call method to rotate image for yaw value
            [self rotateImage:_spheroImage degrees:-yaw];
            
            float y = accelerometer_data.acceleration.y + 1.0;
            if(y < 0.0) y = 0.0;
            if(y > 2.0) y = 2.0;
            y = y * 0.5;
            _accelyLabel.text = [NSString stringWithFormat:@"%1.2f", (y)];
            
            float x = accelerometer_data.acceleration.x;
            y = accelerometer_data.acceleration.y * -1.0;
            float xOffset = x * 20.0;
            float yOffset = y * 20.0;
            _accelxLabel.text = [NSString stringWithFormat:@"%1.2f", (x)];
            
            CGFloat centerX = _spheroCenterHorizontal.constant + xOffset;
            if (centerX > self.view.bounds.size.width / 2) {
                centerX = self.view.bounds.size.width / 2;
            }
            else if (centerX < -self.view.bounds.size.width / 2) {
                centerX = -self.view.bounds.size.width / 2;
            }
            
            CGFloat centerY = _spheroCenterVertical.constant + yOffset;
            if (centerY > self.view.bounds.size.height / 2) {
                centerY = self.view.bounds.size.height / 2;
            }
            else if (centerY < -self.view.bounds.size.height / 2) {
                centerY = -self.view.bounds.size.height / 2;
            }

            _spheroCenterHorizontal.constant = centerX;
            _spheroCenterVertical.constant = centerY;
        }
    }
}

-(void) rotateImage:(UIImageView *) imageView degrees:(CGFloat) degrees{
    CGAffineTransform transform = CGAffineTransformMakeRotation(DEGREES_TO_RADIANS(degrees));
    imageView.transform = transform;
}

@end