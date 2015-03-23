//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>

@interface ViewController()

@property (retain, nonatomic) IBOutlet UISwitch *headingSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *sleepSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *controlSystemSwitch;
@property (retain, nonatomic) IBOutlet UILabel *selfLevelStatusLabel;
@property (retain, nonatomic) IBOutlet UITextField *angleLimitTextField;
@property (retain, nonatomic) IBOutlet UITextField *timeoutTextField;
@property (retain, nonatomic) IBOutlet UITextField *accuracyTextField;

@property (strong, nonatomic) RKConvenienceRobot *robot;

@end

@implementation ViewController

-(void)viewDidLoad {
    [super viewDidLoad];
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
    [[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
}

-(void)appWillResignActive:(NSNotification*)notification {
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [RKRobotDiscoveryAgent stopDiscovery];
    [RKRobotDiscoveryAgent disconnectAll];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
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
    // Handle robot connecting here
}

- (void)handleConnected {
    if ([_robot.robot isKindOfClass:[RKRobotLE class]]) {
        [_robot sleep];
        [[[UIAlertView alloc] initWithTitle:@"Incompatible Robot"
                                    message:@"Ollie robots cannot execute the self level algorithm"
                                   delegate:nil
                          cancelButtonTitle:@"OK"
                          otherButtonTitles:nil] show];
        return;
    }

}

- (void)handleDisconnected {
    // Handle robot disconnected here
}

- (void)handleAsyncData:(RKAsyncMessage *)asyncData{
    // Check if the type of async data returned is a self level response
    if ([asyncData isKindOfClass:[RKSelfLevelCompleteAsyncData class]]) {
        // Grab specific self level response async data
        RKSelfLevelCompleteAsyncData *selfLevelCompleteAsyncData = (RKSelfLevelCompleteAsyncData *)asyncData;
        
        // Print the result code to the user
        switch (selfLevelCompleteAsyncData.resultCode) {
            case RKSelfLevelCompleteResultCodeUnknown:
                _selfLevelStatusLabel.text = @"Unknown Error.";
                break;
            case RKSelfLevelCompleteResultCodeTimeOut:
                _selfLevelStatusLabel.text = @"Timeout.";
                break;
            case RKSelfLevelCompleteResultCodeSensorsError:
                _selfLevelStatusLabel.text = @"Sensor Error.";
                break;
            case RKSelfLevelCompleteResultCodeSelfLevelDisable:
				_selfLevelStatusLabel.text = @"Disabled.";
                break;
            case RKSelfLevelCompleteResultCodeAborted:
                _selfLevelStatusLabel.text = @"Aborted.";
                break;
            case RKSelfLevelCompleteResultCodeChargerNotFound:
                _selfLevelStatusLabel.text = @"Charger Not Found";
                break;
            case RKSelfLevelCompleteResultCodeSuccess:
                _selfLevelStatusLabel.text = @"Complete.";
                break;
        }
    }
}

-(IBAction)abortPressed:(id)sender {
    // Let the user know we sent the abort command
    _selfLevelStatusLabel.text = @"Aborting...";
    // Send abort command
	[_robot sendCommand:[[RKSelfLevelCommand alloc] initWithOptions:0 angleLimit:0 timeout:0 accuracy:0]];
}

-(IBAction)selfLevelPressed:(id)sender {
    NSString *feildText = nil;
    uint8_t angleLimit = 0;
    uint8_t timeout = 0;
    uint8_t accuracy = 0;
    
    // Get the values of the text fields
    feildText = self.angleLimitTextField.text;
    if ([feildText length] > 0) {
        // 0 defaults to Sphero's value of 2 degrees
        angleLimit = [feildText integerValue];
    }
    feildText = self.timeoutTextField.text;
    if ([feildText length] > 0) {
        // 0 defaults to Sphero's value of 15 seconds
        timeout = [feildText integerValue];
    }
    feildText = self.accuracyTextField.text;
    if ([feildText length] > 0) {
        // 0 defaults to Sphero's value of 30 (300 milliseconds within angle limit)
        accuracy = [feildText integerValue];
    }
    
    RKSelfLevelCommandOptions options = RKSelfLevelCommandOptionStart;
    
    // Add keep heading flag
    if(_headingSwitch.isOn) options |= RKSelfLevelCommandOptionKeepHeading;
    
    // Add sleep after level flag
    if(_sleepSwitch.isOn) options |= RKSelfLevelCommandOptionSleepAfter;
    
    // Add control system on flag
    if(_controlSystemSwitch.isOn) options |= RKSelfLevelCommandOptionControlSystemOn;
    
    // Notify user we sent the command
    _selfLevelStatusLabel.text = @"Self Leveling...";
	
	[_robot sendCommand:[[RKSelfLevelCommand alloc] initWithOptions:options angleLimit:angleLimit timeout:timeout accuracy:accuracy]];
}

// Dismiss keyboard when view is tapped
-(IBAction)dismissKeyboard:(id)sender {
    [_angleLimitTextField resignFirstResponder];
    [_timeoutTextField resignFirstResponder];
    [_accuracyTextField resignFirstResponder];
}

@end