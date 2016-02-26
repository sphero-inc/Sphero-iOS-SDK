//
//  RKStatOdometerHack.h
//  RobotCommandKit
//
//  Created by wes on 9/25/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRollCommand.h"
#import "RKImmutableCommand.h"

@interface RKStatOdometerHack : NSObject

+ (void)recordStatForPacket:(NSData *)packet andMac:(NSString *)mac;

@end
