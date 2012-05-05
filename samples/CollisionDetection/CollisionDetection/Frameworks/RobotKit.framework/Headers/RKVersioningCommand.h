//
//  RKVersioningCommand.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>

@class RKRobot;

/*!
 * @brief Class that encapsulates a request for version information from the robot.
 *
 * This is a simple command that requires no parameters. The version information is returned
 * in the response.
 *
 * @sa RKVersioningResponse
 */
@interface RKVersioningCommand : RKDeviceCommand {

}

@end
