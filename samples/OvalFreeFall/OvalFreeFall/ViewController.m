//
//  ViewController.m
//  OvalFreeFall
//
//  Created by Paul Trebilcox on 10/27/15.
//  Copyright © 2015 Sphero. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>

@interface ViewController () <RKOvalControlDelegate>

@property (nonatomic, strong) RKConvenienceRobot *robot;
@property (nonatomic, strong) RKOvalControl *ovalControl;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appWillResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    
    
    // hook up for robot state changes
    [[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)appDidBecomeActive:(NSNotification *)note {
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