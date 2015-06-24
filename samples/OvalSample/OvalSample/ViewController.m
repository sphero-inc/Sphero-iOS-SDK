//
//  ViewController.m
//  OvalSample
//
//  Created by Corey Earwood on 6/23/15.
//  Copyright (c) 2015 Orbotix. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>

@interface ViewController () <RKOvalControlDelegate>

@property (nonatomic, weak) IBOutlet UITextField *lightSpeed;
@property (nonatomic, strong) RKConvenienceRobot *robot;
@property (nonatomic, strong) RKOvalControl *ovalControl;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)updateOval:(id)sender {
    [_ovalControl sendOvalString:[NSString stringWithFormat:@"speed = %@;...",_lightSpeed.text]];
}

- (void)appDidBecomeActive:(NSNotification *)note {
    [[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
    [RKRobotDiscoveryAgent startDiscovery];
}

- (void)appWillResignActive:(NSNotification *)note {
    [RKRobotDiscoveryAgent disconnectAll];
}

- (void)handleRobotStateChangeNotification:(RKRobotChangedStateNotification *)notification {
    switch (notification.type) {
        case RKRobotOnline:
            self.robot = [[RKConvenienceRobot alloc] initWithRobot:notification.robot];
            self.ovalControl = [[RKOvalControl alloc] initWithRobot:notification.robot delegate:self];
            [self.ovalControl resetOvmAndLibrary:YES];
            [self sendOvalProgram];
            break;
            
        default:
            break;
    }
}

- (void)sendOvalProgram {
    NSString *ovalProgram = [NSString stringWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"Sample" ofType:@"oval"] encoding:NSUTF8StringEncoding error:nil];
    [_ovalControl sendOvalPrograms:@[ovalProgram]];
}

#pragma mark - RKOvalControlDelegate

- (void)ovalControlDidFinishSendingProgram:(RKOvalControl *)control {
    NSLog(@"Oval successfully sent");
}

- (void)ovalControlDidResetOvm:(RKOvalControl *)control {
    NSLog(@"OVM Reset");
}

- (void)ovalControl:(RKOvalControl *)control receivedOvalNotification:(RKOvalDeviceBroadcast *)notification {
    NSLog(@"Did receive oval async with floats: %@ ints: %@",notification.floats, notification.ints);
}

- (void)ovalControl:(RKOvalControl *)control receivedVmRuntimeError:(RKOvalErrorBroadcast *)notification {
    NSLog(@"Did receive OVM Error: %@",notification.errorDescription);
}

- (void)ovalControl:(RKOvalControl *)control didFailToSendProgramWithMessage:(NSString *)message {
    NSLog(@"Failed tos end program with message: %@",message);
}

@end
