//
//  ViewController.m
//  SelfLevel
//
//  Created by Michael DePhillips on 7/14/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController

@synthesize selfLevelStatusLabel;
@synthesize headingSwitch;
@synthesize sleepSwitch;
@synthesize controlSystemSwitch;
@synthesize angleLimitTextField;
@synthesize timeoutTextField;
@synthesize accuracyTextField;

-(void)dealloc {
    [selfLevelStatusLabel release];
    [headingSwitch release];
    [sleepSwitch release];
    [controlSystemSwitch release];
    [angleLimitTextField release];
    [timeoutTextField release];
    [accuracyTextField release];
    [super dealloc];
}

-(void)viewDidUnload {
    selfLevelStatusLabel = nil;
    headingSwitch = nil;
    sleepSwitch = nil;
    controlSystemSwitch = nil;
    angleLimitTextField = nil;
    timeoutTextField = nil;
    accuracyTextField = nil;
}

-(void)viewDidLoad {
    [super viewDidLoad];
    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
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
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
        ////Register for asynchronous messages 
        [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleAsyncData:)];
    }
    robotOnline = YES;
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    }
}

- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
{
    // Check if the type of async data returned is a self level response
    if ([asyncData isKindOfClass:[RKSelfLevelCompleteAsyncData class]]) {
        
        // Grab specific self level response async data
        RKSelfLevelCompleteAsyncData *selfLevelCompleteAsyncData = (RKSelfLevelCompleteAsyncData *)asyncData;
        
        // Print the result code to the user
        switch(selfLevelCompleteAsyncData.resultCode)
        {
            case RKSelfLevelCompleteResultCodeUnknown:
                selfLevelStatusLabel.text = @"Unknown Error.";
                break;
            case RKSelfLevelCompleteResultCodeTimeOut:
                selfLevelStatusLabel.text = @"Timeout.";
                break;
            case RKSelfLevelCompleteResultCodeSensorsError:
                selfLevelStatusLabel.text = @"Sensor Error.";
                break;
            case RKSelfLevelCompleteResultCodeSelfLevelDisable:
                    selfLevelStatusLabel.text = @"Disabled.";
                break;
            case RKSelfLevelCompleteResultCodeAborted:
                selfLevelStatusLabel.text = @"Aborted.";
                break;
            case RKSelfLevelCompleteResultCodeChargerNotFound:
                selfLevelStatusLabel.text = @"Charger Not Found";
                break;
            case RKSelfLevelCompleteResultCodeSuccess:
                selfLevelStatusLabel.text = @"Complete.";
                break;
        }
    }
}

-(IBAction)abortPressed:(id)sender {
    // Let the user know we sent the abort command
    selfLevelStatusLabel.text = @"Aborting...";
    // Send abort command
    [RKSelfLevelCommand sendCommandAbortSelfLevel];
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
    if( headingSwitch.isOn ) options |= RKSelfLevelCommandOptionKeepHeading;
    
    // Add sleep after level flag
    if( sleepSwitch.isOn ) options |= RKSelfLevelCommandOptionSleepAfter;
    
    // Add control system on flag
    if( controlSystemSwitch.isOn) options |= RKSelfLevelCommandOptionControlSystemOn;
    
    // Notify user we sent the command
    selfLevelStatusLabel.text = @"Self Leveling...";
    
    [RKSelfLevelCommand sendCommandWithOptions:options 
                                    angleLimit:angleLimit 
                                       timeout:timeout 
                                      accuracy:accuracy];
}

// Dismiss keyboard when view is tapped
-(IBAction)dismissKeyboard:(id)sender {
    [angleLimitTextField resignFirstResponder];
    [timeoutTextField resignFirstResponder];
    [accuracyTextField resignFirstResponder];
}

@end
