//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Command to get the current device mode.
 * 
 * Command to get the current device mode. The mode is returned in the response.
 * @sa RKGetDeviceModeResponse
 */
@interface RKGetDeviceModeCommand : RKDeviceCommand

+(instancetype) command;

@end
