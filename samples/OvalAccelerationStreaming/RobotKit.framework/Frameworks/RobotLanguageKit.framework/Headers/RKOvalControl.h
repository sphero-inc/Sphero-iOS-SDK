//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RobotCommandKit.h>
#import "RKOvalDeviceBroadcast.h"
#import "RKOvalErrorBroadcast.h"

@class RKOvalControl;

@protocol RKOvalControlDelegate <NSObject>

- (void)ovalControl:(RKOvalControl *)control didFailToSendProgramWithMessage:(NSString *)message;
- (void)ovalControlDidFinishSendingProgram:(RKOvalControl *)control;
- (void)ovalControlDidResetOvm:(RKOvalControl *)control;
- (void)ovalControl:(RKOvalControl *)control receivedOvalNotification:(RKOvalDeviceBroadcast *)notification;
- (void)ovalControl:(RKOvalControl *)control receivedVmRuntimeError:(RKOvalErrorBroadcast *)notification;

@end

@interface RKOvalControl : NSObject

@property (nonatomic) BOOL enableCompileReportOutput;

+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)controlWithRobot:(id<RKRobotBase>)robot delegate:(id<RKOvalControlDelegate>)delegate;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithRobot:(id<RKRobotBase>)robot delegate:(id<RKOvalControlDelegate>)delegate;

- (void)resetOvmAndLibrary:(BOOL)resetLibrary;

- (void)sendOvalString:(NSString *)program;
- (void)sendOvalString:(NSString *)program allowQueue:(BOOL)allowsQueue;
- (void)sendOvalPrograms:(NSArray *)programs;

@end
