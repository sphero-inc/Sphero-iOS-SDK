//
//  RKFlashWritingCommandDetector.h
//  RobotCommandKit
//
//  Created by Hunter Lang on 12/2/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

@interface RKFlashWritingCommandDetector : NSObject

+(BOOL)isFlashWritingCommand:(RKDeviceCommand *)command;

@end
