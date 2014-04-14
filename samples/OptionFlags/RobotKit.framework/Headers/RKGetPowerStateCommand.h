//
//  RKGetPowerStateCommand.h
//  RobotKit
//
//  Created by Brian Smith on 2/21/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Command to request the power state from a Robot.
 *
 * Command to request the current power state from a Robot. This data is returned in a RKGetPowerStateResponse 
 * object to observer registered with RKDeviceMessenger.
 * 
 * @sa RKGetPowerStateResponse
 * @sa RKDeviceMessenger
 */
@interface RKGetPowerStateCommand : RKDeviceCommand

@end
