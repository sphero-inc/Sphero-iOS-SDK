//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>

@interface ViewController()

@property (strong, nonatomic) IBOutlet UITextField *textFieldNewX;
@property (strong, nonatomic) IBOutlet UITextField *textFieldNewY;
@property (strong, nonatomic) IBOutlet UITextField *textFieldNewYaw;

@property (strong, nonatomic) IBOutlet UISwitch *flagSwitch;

@property (strong, nonatomic) IBOutlet UILabel *xValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *yValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *xVelocityValueLabel;
@property (strong, nonatomic) IBOutlet UILabel *yVelocityValueLabel;

@property (nonatomic) BOOL ledON;
@property (strong, nonatomic) RUICalibrateGestureHandler *calibrateHandler;
@property (strong, nonatomic) RKConvenienceRobot *robot;

@end

#define VELOCITY 0.4

@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    self.calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];

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

- (void)appDidBecomeActive:(BOOL)animated {
    [RKRobotDiscoveryAgent startDiscovery];
}

- (void)appWillResignActive:(NSNotification*)n {
    [RKRobotDiscoveryAgent stopDiscovery];
    [RKRobotDiscoveryAgent disconnectAll];
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
    [_robot addResponseObserver:self];
    [self startLocatorStreaming];
    [self.calibrateHandler setRobot:self.robot.robot];
}

- (void)handleDisconnected {
    [_robot removeResponseObserver:self];
    [_calibrateHandler setRobot:nil];
}

- (void)startLocatorStreaming {
    // Register for Locator X,Y position, and X,Y velocity
    RKDataStreamingMask sensorMask = RKDataStreamingMaskLocatorAll;
	[self.robot sendCommand:[RKSetDataStreamingCommand commandWithRate:10 andMask:sensorMask]];
}

- (void)handleAsyncMessage:(RKAsyncMessage *)message forRobot:(id<RKRobotBase>)robot {
    if ([message isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        
        // Grab specific sensor data objects from the main sensor object
        RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)message;
        RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
        RKLocatorData *locatorData = sensorsData.locatorData;
        
        // Print Locator Values
        self.xValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.position.x, @"cm"];
        self.yValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.position.y, @"cm"];
        self.xVelocityValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.velocity.x, @"cm/s"];
        self.yVelocityValueLabel.text = [NSString stringWithFormat:@"%.02f  %@", locatorData.velocity.y, @"cm/s"];
    }
}

- (IBAction)configurePressed:(id)sender {
    
    NSString *fieldText = nil;
    int16_t newX = 0;
    int16_t newY = 0;
    int16_t newYaw = 0;
    
    // Get the values of the text fields
    fieldText = self.textFieldNewX.text;
    if ([fieldText length] > 0) {
        newX = [fieldText integerValue];
    }
    fieldText = self.textFieldNewY.text;
    if ([fieldText length] > 0) {
        newY = [fieldText integerValue];
    }
    fieldText = self.textFieldNewYaw.text;
    if ([fieldText length] > 0) {
        newYaw = [fieldText integerValue];
    }

	
    // Convert the value of the toggle switch to the configure locator flag
    RKConfigureLocatorFlag flag = (_flagSwitch.isOn ? RKConfigureLocatorRotateWithCalibrateFlagOn : RKConfigureLocatorRotateWithCalibrateFlagOff );
    
    // Send command to configure locactor
    // After sending the command, you should see the x and y values of the labels
    // change to the ones you specified in the text fields
	[self.robot sendCommand:[[RKConfigureLocatorCommand alloc] initForFlag:flag newX:newX newY:newY newYaw:newYaw]];
}

- (IBAction)upPressed:(id)sender {
	[self.robot sendCommand:[RKRollCommand commandWithHeading:0 andVelocity:VELOCITY]];
}

- (IBAction)downPressed:(id)sender {
	[self.robot sendCommand:[RKRollCommand commandWithHeading:180 andVelocity:VELOCITY]];
}

- (IBAction)leftPressed:(id)sender {
	[self.robot sendCommand:[RKRollCommand commandWithHeading:270 andVelocity:VELOCITY]];
}

- (IBAction)rightPressed:(id)sender {
	[self.robot sendCommand:[RKRollCommand commandWithHeading:90 andVelocity:VELOCITY]];
}

- (IBAction)stopPressed:(id)sender {
    [self.robot stop];
}

// Dismiss keyboard when view is tapped
- (IBAction)dismissKeyboard:(id)sender {
    [_textFieldNewX resignFirstResponder];
    [_textFieldNewY resignFirstResponder];
    [_textFieldNewYaw resignFirstResponder];
}

@end
