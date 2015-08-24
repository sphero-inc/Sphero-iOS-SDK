//
//  RKLeTouchConnectStrategy.h
//  RobotKitLE
//
//  Created by wes on 9/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"



@interface RKLeProximityConnectStrategy : NSObject <RKLeConnectStrategy>

// in % 0 - 100
- (void)setConnectionSignalStrengthThresholdValue:(int)threshold;


@end
