//
//  RKLeBatchConnectStrategy.h
//  RobotKitLE
//
//  Created by Corey Earwood on 9/9/15.
//  Copyright (c) 2015 Sphero. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"

@interface RKLeBatchConnectStrategy : NSObject <RKLeConnectStrategy>

+ (instancetype)strategy NS_UNAVAILABLE;
+ (instancetype)connectStrategyByBatchingStrategies:(NSArray *)connectStrategies;

@end
