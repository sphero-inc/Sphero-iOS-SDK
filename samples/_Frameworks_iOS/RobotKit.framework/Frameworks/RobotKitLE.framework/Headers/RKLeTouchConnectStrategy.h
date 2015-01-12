//
//  RKLeTouchConnectStrategy.h
//  RobotKitLE
//
//  Created by wes on 9/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"

// use caution - Touch is only safe setting as of 9/09/14
typedef NS_ENUM(uint8_t, RKLEConnectThreshold){
	RKLEConnectThresholdTouch = 0,
	RKLEConnectThresholdNear = 1,
	RKLEConnectThresholdRoom = 2,
};


@interface RKLeTouchConnectStrategy : NSObject <RKLeConnectStrategy>

@property (readwrite) RKLEConnectThreshold connectRssiIndex;

@end
