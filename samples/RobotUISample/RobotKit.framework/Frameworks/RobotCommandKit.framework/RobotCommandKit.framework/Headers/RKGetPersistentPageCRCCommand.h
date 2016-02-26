//
//  RKGetPersistentPageCRCCommand.h
//  RobotCommandKit
//
//  Created by Corey Earwood on 4/28/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKGetPersistentPageCRCCommand : RKDeviceCommand

+ (instancetype)commandWithBlockId:(ushort)blockId;
- (instancetype)initWithBlockId:(ushort)blockId;

@end
