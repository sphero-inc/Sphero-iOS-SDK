//
//  RKGetDeviceModeResponse.h
//  RobotKit
//
//  Created by Brian Smith on 7/13/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RKDeviceResponse.h>

/*! enumeration of modes a robot can be set to. */
enum RKDeviceMode {
    /*! Normal mode which is the default operation mode. */
    RKDeviceModeNormal = 0,
    /*! User hack mode. This mode enables ASCII shell command. Refer to the shell commands document
     for further details. */
    RKDeviceModeUserHack = 1
};
/*! Type for enumerated device modes. */
typedef enum RKDeviceMode RKDeviceMode;

/*!
 * Response class for get device mode commands . The mode is returned in the response, which is an enumerated value.
 * Client code needs to register an observer with RKDeviceMesssenger in order to receive the response object.
 *
 * @sa RKGetDeviceModeCommand
 * @sa RKSetUserHackModeCommand
 * @sa RKDeviceMessenger
 */
@interface RKGetDeviceModeResponse : RKDeviceResponse {
    @private
    RKDeviceMode mode;
}

/*! The mode the device is set to. */
@property (nonatomic, readonly) RKDeviceMode mode;

@end
