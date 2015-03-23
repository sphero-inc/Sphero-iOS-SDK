//
//  RKGetPowerStateCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 2/21/12.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Command to request the power state from a Robot.
 * 
 * @sa RKGetPowerStateResponse
 */
@interface RKGetPowerStateCommand : RKDeviceCommand

+(instancetype) command;

@end
