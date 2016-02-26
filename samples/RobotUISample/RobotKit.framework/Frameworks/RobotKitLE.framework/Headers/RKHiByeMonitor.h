//
//  RKHiByeMonitor.h
//  LeTestDrive
//
//  Created by wes on 5/12/15.
//  Copyright (c) 2015 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRobotLE.h"

@protocol RKHiByeMonitorDelegate <NSObject>

@optional
-(void) robotDidSayHi:(RKRobotLE*) robot withUserInfo:(NSDictionary*) userInfo;
-(void) robotDidSayBye:(RKRobotLE*) robot withUserInfo:(NSDictionary*) userInfo;
@end

@interface RKHiByeMonitor : NSObject

-(id) initWithDelegate:(id<RKHiByeMonitorDelegate>) delegate;

-(id) initWithHiThreshold:(uint8_t) hiThreshold andByeThreshold:(uint8_t) byeThreshold;

-(void) enableRemoteRSSIMonitor:(RKRobotLE*) robot withInterval:(uint16_t) interval;

@end
