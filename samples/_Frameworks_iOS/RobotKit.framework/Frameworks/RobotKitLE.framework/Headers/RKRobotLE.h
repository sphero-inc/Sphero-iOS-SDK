//
//  Copyright (c) 2013-2014 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <RobotCommandKit/RobotCommandKit.h>
#import <RobotCommandKit/RKRobotBase.h>
#import "RKLeConnectStrategy.h"
#import "RKLeRobotLink.h"

extern NSString * const kRobotRadioDidACK;
extern NSString * const kRobotDidUpdateRSSI;
extern NSString * const kRobotDidGetCloseNotification;


typedef NS_ENUM(uint8_t, RKSleepType) {
	RKSleepNoMore,
	RKSleep,          // regular sleep - robot advertises at high rate with
	RKSleepLowPower,
	RKSleepDeep
};


@interface RKRobotLE : NSObject <RKRobotBase, RKLeNode, RKLinkDelegate, RKSessionDelegate>

/*! BLE Radio Stack */
@property (strong, nonatomic, readonly) RKLeRobotLink *radioLink;

#pragma cached values - asyncronously updated on command calls
@property (readonly) NSNumber* lastOdometerReading;
@property (readonly) RKVersioningResponse* versions;

-(NSNumber*) connectTimeInSeconds;


#pragma mark - ble radio control service

/*! request the robot sleep - upon internal callback that sleepDidOccur, SDK disconnects by default. */
-(void) sleep:(RKSleepType) sleepType;


@end
