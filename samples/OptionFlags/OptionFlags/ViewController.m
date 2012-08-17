//
//  ViewController.m
//  OptionFlags
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController

@synthesize bit0Label;
@synthesize bit1Label;
@synthesize bit2Label;
@synthesize bit3Label;
@synthesize bit4Label;
@synthesize bit0Switch;
@synthesize bit1Switch;
@synthesize bit2Switch;
@synthesize bit3Switch;
@synthesize bit4Switch;

-(void)dealloc {
    [bit0Label release];
    [bit1Label release];
    [bit2Label release];
    [bit3Label release];
    [bit4Label release];
    [bit0Switch release];
    [bit1Switch release];
    [bit2Switch release];
    [bit3Switch release];
    [bit4Switch release];
    [super dealloc];
}

-(void)viewDidUnload {
    bit0Label = nil;
    bit1Label = nil;
    bit2Label = nil;
    bit3Label = nil;
    bit4Label = nil;
    bit0Switch = nil;
    bit1Switch = nil;
    bit2Switch = nil;
    bit3Switch = nil;
    bit4Switch = nil;
    [super viewDidUnload];
}

-(void)viewDidLoad {
    [super viewDidLoad];
    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillTerminate:) name:UIApplicationWillTerminateNotification object:nil];

    /*Robot is now online*/
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

-(void)appWillTerminate:(NSNotification*)notification {
    /* Unregister to get response */
    [[RKDeviceMessenger sharedMessenger] removeResponseObserver:self];
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    
    // If you want the option flags to be permanent, remove this next line
    [RKSetOptionFlagsCommand sendCommand];
    
    // Close connection will put Sphero back in its default state before connecting
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
        /* Register to get the response of the get option flags command */
        [[RKDeviceMessenger sharedMessenger] addResponseObserver:self selector:@selector(handleResponse:)];
        /* Send command to request option flags */
        [RKGetOptionFlagsCommand sendCommand];
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

-(void)handleResponse:(RKDeviceResponse *)response {
    // Only respond to get option flags responses
    if( [response isKindOfClass:[RKGetOptionFlagsResponse class]] ) {
        RKGetOptionFlagsResponse* optionFlagsResponse = (RKGetOptionFlagsResponse*) response;

        // Display the current option flags as true/false labels
        self.bit0Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsPreventSleepInCharger]) ? @"true":@"false";
        
        self.bit1Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsEnableVectorDrive]) ? @"true":@"false";
        
        self.bit2Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsDisableSelfLevelInCharger]) ? @"true":@"false";
        
        self.bit3Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsTailLightAlwaysOn]) ? @"true":@"false";
        
        self.bit4Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsEnableMotionTimeout]) ? @"true":@"false";
    }
}

-(IBAction)getOptionFlagsPressed:(id)sender {
    [RKGetOptionFlagsCommand sendCommand];
}

-(IBAction)setOptionFlagsPressed:(id)sender {
    
    RKGetOptionFlagsMask optionFlags = 0;
    
    // Add prevent sleep in charger flag value
    if( bit0Switch.isOn ) optionFlags |= RKGetOptionFlagsPreventSleepInCharger;
    
    // Add enable vector drive flag value
    if( bit1Switch.isOn ) optionFlags |= RKGetOptionFlagsEnableVectorDrive;
    
    // Add disable self level in charger flag level
    if( bit2Switch.isOn) optionFlags |= RKGetOptionFlagsDisableSelfLevelInCharger;
    
    // Add tail light always on flag
    if( bit3Switch.isOn) optionFlags |= RKGetOptionFlagsTailLightAlwaysOn;
    
    // Add enable motion timeout flag
    if( bit4Switch.isOn) optionFlags |= RKGetOptionFlagsEnableMotionTimeout;
    
    // Send command to set option flags
    [RKSetOptionFlagsCommand sendCommandWithOptionFlags:optionFlags];
}

-(IBAction)restoreDefaultsPressed:(id)sender {
    [RKSetOptionFlagsCommand sendCommand];
}

@end
