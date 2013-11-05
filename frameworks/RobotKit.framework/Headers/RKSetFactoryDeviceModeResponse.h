//
//  RKSetFactoryDeviceModeResponse.h
//  RobotKit
//
//  Created by Adam Wilson on 7/3/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//
#import <RobotKit/RKDeviceResponse.h>

/*!
 * Simple response to a set device mode command.
 * @sa SetDeviceModeCommand
 */
@interface RKSetFactoryDeviceModeResponse : RKDeviceResponse {
    UInt32 Rn;
}

@property (nonatomic) UInt32 Rn;

@end
