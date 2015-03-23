//
//  RKVersioningCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 5/27/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

@class RKRobotClassic;


/*!
 * @brief Class that encapsulates a request for version information from the robot.
 *
 * This is a simple command that requires no parameters. The version information is returned
 * in the response.
 *
 * @sa RKVersioningResponse
 */
@interface RKVersioningCommand : RKDeviceCommand

+(instancetype) command;

@end
