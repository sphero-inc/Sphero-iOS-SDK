//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"


/*! enumeration of modes a robot can be set to. */
typedef NS_ENUM(uint8_t, RKDeviceMode ){
	/*! Normal mode which is the default operation mode. */
	RKDeviceModeNormal = 0,
	/*! User hack mode. This mode enables ASCII shell command. Refer to the shell commands document for further details. */
	RKDeviceModeUserHack = 1,
	/*! Factory Mode.  This mode is enabled at the factory and is not a mode that can be set after leaving the factory. */
	RKDeviceModeFactory = 2
};


/*!
 * Response class for get device mode commands . The mode is returned in the response, which is an enumerated value.
 * Client code needs to register an observer with RKDeviceMesssenger in order to receive the response object.
 *
 * @sa RKGetDeviceModeCommand
 * @sa RKSetUserHackModeCommand
 */
@interface RKGetDeviceModeResponse : RKDeviceResponse

/*! The mode the device is set to. */
@property ( nonatomic, readonly ) RKDeviceMode mode;

@end
