//
//  ViewController.m
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotUIKit/RobotUIKit.h"
#import "RobotKit/RKRunMacroCommand.h"
#import "RobotKit/RKAbortMacroCommand.h"
#import "RobotKit/RKAbortMacroResponse.h"

@implementation ViewController


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillTerminate:) name:UIApplicationWillTerminateNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

-(void)appWillTerminate:(NSNotification*)notification {
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    // Abort the Macros
    [RKAbortMacroCommand sendCommand];
    // Closing the connection will put Sphero back into its default state
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}


#pragma mark-Sphero Connection
- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
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

#pragma mark-Macros
-(IBAction)macro1:(id)sender{
    //Call for the binary file "storbelight" and change into a a data packet
    NSString *file = [[NSBundle mainBundle] pathForResource:@"strobelight" ofType:@"sphero"];
    NSData *data = [NSData dataWithContentsOfFile:file];
    
    //saves a temporary macro command thats includes the data packet
    [RKSaveTemporaryMacroCommand sendCommandWithMacro:data flags:RKMacroFlagMotorControl];
    //Run temporary macro 255
    [RKRunMacroCommand sendCommandWithId:255]; 

}

-(IBAction)macro2:(id)sender{
    //Call for the binary file "symboll" and change into a a data packet
    NSString *file = [[NSBundle mainBundle] pathForResource:@"symboll" ofType:@"sphero"];
    NSData *data = [NSData dataWithContentsOfFile:file];
    
    //saves a temporary macro command thats includes the data packet
    [RKSaveTemporaryMacroCommand sendCommandWithMacro:data flags:RKMacroFlagMotorControl];
    //Run temporary macro 255
    [RKRunMacroCommand sendCommandWithId:255]; 

}

-(IBAction)macro3:(id)sender{
    //Call for the binary file "dance1" and change into a a data packet
    NSString *file = [[NSBundle mainBundle] pathForResource:@"dance1" ofType:@"sphero"];
    NSData *data = [NSData dataWithContentsOfFile:file];
    
    //saves a temporary macro command thats includes the data packet
    [RKSaveTemporaryMacroCommand sendCommandWithMacro:data flags:RKMacroFlagMotorControl];
    //Run temporary macro 255
    [RKRunMacroCommand sendCommandWithId:255]; 

}

-(IBAction)macro4:(id)sender{
    //Call for the binary file "bigdance" and change into a a data packet
    NSString *file = [[NSBundle mainBundle] pathForResource:@"bigdance" ofType:@"sphero"];
    NSData *data = [NSData dataWithContentsOfFile:file];
    
    //saves a temporary macro command thats includes the data packet
    [RKSaveTemporaryMacroCommand sendCommandWithMacro:data flags:RKMacroFlagMotorControl];
    //Run temporary macro 255
    [RKRunMacroCommand sendCommandWithId:255]; 
  
}

-(IBAction)stop:(id)sender {
    // Abort Macro Command
    [RKAbortMacroCommand sendCommand];   
    [RKStabilizationCommand sendCommandWithState:(RKStabilizationStateOn)];
}



@end
