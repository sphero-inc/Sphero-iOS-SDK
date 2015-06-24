//
//  RKSetFactoryDeviceModeResponse.h
//  RobotKit
//
//  Created by Adam Wilson on 7/3/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//
#import "RKDeviceResponse.h"

/*!
 * Simple response to a set device mode command.
 * @sa SetDeviceModeCommand
 */
@interface RKSetFactoryDeviceModeResponse : RKDeviceResponse

@property (nonatomic, readonly) UInt32 Rn;

@end
