//
//  RKStatForCommandFactory.h
//  RobotKitLE
//
//  Created by Hunter Lang on 7/14/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKStat.h"

@interface RKStatForPacketFactory : NSObject

+ (RKStat *)statForPacket:(NSData *)packet identifier:(NSString *)usuallyMac;

@end
