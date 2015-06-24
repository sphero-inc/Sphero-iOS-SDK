//
//  RKLeClosestConnectStrategy.h
//  RobotKitLE
//
//  Created by wes on 9/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"

/*! connect to the closest robot - wait 2s for the RSSI values to stabilize the list */
@interface RKLeClosestConnectStrategy : NSObject <RKLeConnectStrategy>

@property (readwrite) int guardTime;

@end
