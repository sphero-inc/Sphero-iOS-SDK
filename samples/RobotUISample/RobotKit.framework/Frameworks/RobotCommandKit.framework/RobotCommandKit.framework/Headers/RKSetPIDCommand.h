//
//  RKSetPIDValuesCommand.h
//  RobotCommandKit
//
//  Created by wes on 8/20/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

typedef NS_ENUM(Byte, RKAxis){
	RKPitchAxis = 0x00,
	RKRollAxis = 0x01,
	RKYawAxis = 0x02
};

@interface RKSetPIDCommand : RKDeviceCommand

-(instancetype) initWithAxis:(RKAxis) axis andP:(NSNumber*) p andI:(NSNumber*)i andD:(NSNumber*)d;

@end
