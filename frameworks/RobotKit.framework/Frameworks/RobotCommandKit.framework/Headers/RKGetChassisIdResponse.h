//
//  RKGetChassisIdResponse.h
//  RobotCommandKit
//
//  Created by wes on 4/17/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKGetChassisIdResponse : RKDeviceResponse

@property (strong, nonatomic) NSNumber* chassisId;

@end
