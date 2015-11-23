//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import "HelloWorldViewController.h"
#import <RobotKit/RobotKit.h>

@interface HelloWorldViewController()

@property (nonatomic) BOOL ledOn;
@property (strong, nonatomic) IBOutlet UILabel* connectionLabel;
@property (strong, atomic) RKConvenienceRobot* robot;

@end

@implementation HelloWorldViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];

	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(appWillResignActive:)
												 name:UIApplicationWillResignActiveNotification
											   object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(appDidBecomeActive:)
												 name:UIApplicationDidBecomeActiveNotification
											   object:nil];
}

- (void)appDidBecomeActive:(NSNotification*)n {
	[self startDiscovery];
}

- (void)appWillResignActive:(NSNotification*)n {
	[RKRobotDiscoveryAgent stopDiscovery];
	[_connectionLabel setText:@"Sleeping"];
    [RKRobotDiscoveryAgent disconnectAll];
}

- (void)startDiscovery {
	_connectionLabel.text = @"Discovering Robots";
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
    [_connectionLabel setText:[NSString stringWithFormat:@"%@ Connecting", _robot.robot.name]];
}

- (void)handleConnected {
    [_connectionLabel setText:_robot.robot.name];
    [self toggleLED];
}

- (void)handleDisconnected {
    _connectionLabel.text = @"Disconnected";
    [self startDiscovery];
}

- (IBAction)onDisconnectPressed:(id)sender {
    if (_robot) {
		[_connectionLabel setText:@"Disconnecting..."];
		[_robot sleep];
    }
}

- (void)toggleLED {
	if(!_robot || ![_robot isConnected]) return; // stop the toggle if no robot.

    if (_ledOn) {
		[_robot setLEDWithRed:1 green:0 blue:0];
    }
    else {
		[_robot setLEDWithRed:0 green:0 blue:1];
    }
    _ledOn = !_ledOn;
    [self performSelector:@selector(toggleLED) withObject:nil afterDelay:0.5];
}

@end
