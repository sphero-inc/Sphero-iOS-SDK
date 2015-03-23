//
//  Copyright (c) 2014 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import "EAGLView.h"

@interface ViewController ()

@property (strong, nonatomic) IBOutlet EAGLView *eaglView;
@property (strong, nonatomic) IBOutlet UILabel *robotStatusLabel;
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
        default:
            break;
    }
}

- (void)handleConnecting {
    [_robotStatusLabel setText:@"Robot connecting"];
}

- (void)handleConnected {
    [_robotStatusLabel setText:@"Robot connected"];
    [self.robot enableStablilization:NO];
    [self.robot addResponseObserver:self];
    [self.robot enableSensors:RKDataStreamingMaskAccelerometerFilteredAll
              atStreamingRate:20];
    [_eaglView startAnimation];
}

- (void)handleDisconnected {
    [_robotStatusLabel setText:@"Robot disconnected"];
    [_eaglView stopAnimation];
}

-(void) handleAsyncMessage:(RKAsyncMessage *)message forRobot:(id<RKRobotBase>)robot {
    // Need to check which type of async data is received as this method will be called for
    // data streaming packets and sleep notification packets. We are going to ingnore the sleep
    // notifications.
    if ([message isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        // Received sensor data, so display it to the user.
        RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)message;
        RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
        RKAccelerometerData *accelerometerData = sensorsData.accelerometerData;
        RKAcceleration accelerationData = accelerometerData.acceleration;
        [_eaglView setRotationWithAccelerometerX:accelerationData.x Y:accelerationData.y Z:accelerationData.z];
    }
}

@end
