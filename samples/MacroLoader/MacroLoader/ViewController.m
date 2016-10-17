//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>

@interface ViewController()

@property (strong, nonatomic) RKConvenienceRobot *robot;

@end

@implementation ViewController

- (void)viewDidLoad {
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

- (void)appDidBecomeActive:(NSNotification *)n {
    [RKRobotDiscoveryAgent startDiscovery];
}

- (void)appWillResignActive:(NSNotification *)n {
	[_robot macroAbort];
    [RKRobotDiscoveryAgent disconnectAll];
    [RKRobotDiscoveryAgent stopDiscovery];
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
    // Handle robot connecting here
}

- (void)handleConnected {
    // Handle robot connected here
}

- (void)handleDisconnected {
    // Handle robot disconnected here
}

- (IBAction)macro1:(id)sender {
	//Call for the binary file "strobelight" and change into a a data packet
	NSString *file = [[NSBundle mainBundle] pathForResource:@"strobelight" ofType:@"sphero"];
	NSData *data = [NSData dataWithContentsOfFile:file];
	
	//saves a temporary macro (255) command thats includes the data packet
	[_robot macroSaveTemporary:data];
	[_robot macroRunAtId:255];
}

- (IBAction)macro2:(id)sender {
	//Call for the binary file "symboll" and change into a a data packet
	NSString *file = [[NSBundle mainBundle] pathForResource:@"symboll" ofType:@"sphero"];
	NSData *data = [NSData dataWithContentsOfFile:file];
	
	//saves a temporary macro command thats includes the data packet
	[_robot macroSaveTemporary:data];
	[_robot sendCommand:[[RKRunMacroCommand alloc] initWithId:255]];
}

- (IBAction)macro3:(id)sender {
	//Call for the binary file "dance1" and change into a a data packet
	NSString *file = [[NSBundle mainBundle] pathForResource:@"dance1" ofType:@"sphero"];
	NSData *data = [NSData dataWithContentsOfFile:file];
	
	//saves a temporary macro command thats includes the data packet
	[_robot macroSaveTemporary:data];
	[_robot sendCommand:[[RKRunMacroCommand alloc] initWithId:255]];
}

- (IBAction)macro4:(id)sender {
	//Call for the binary file "bigdance" and change into a a data packet
	NSString *file = [[NSBundle mainBundle] pathForResource:@"bigdance" ofType:@"sphero"];
	NSData *data = [NSData dataWithContentsOfFile:file];
	
	//saves a temporary macro command thats includes the data packet
	[_robot sendCommand:[[RKSaveTemporaryMacroCommand alloc] initWithMacro:data flags:RKMacroFlagMotorControl delay:0]]; // example of deeper control
	[_robot macroRunAtId:255];
}


- (IBAction)stop:(id)sender {
	[_robot macroAbort];
	[_robot enableStabilization:YES];
}


@end
