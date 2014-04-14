//
//  RKSetDeviceModeCommand.h
//  RobotKit
//
//  Created by Brian Smith on 7/13/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceCommand.h>

/*! 
 * @brief Command to assign the operation mode of Sphero.
 *
 * Command to assign the operation mode of Sphero. The user hack mode enables ASCII shell commands.
 * @sa
 */
@interface RKSetUserHackModeCommand : RKDeviceCommand {
   BOOL mode;
}

/*! 
 * Property for the mode to be set with this command.
 */
@property ( nonatomic, readonly ) BOOL mode;

/*! 
 * Convience method for sending the command for a given mode.
 * @param deviceMode The mode to set for the robot.
 */
+ (void) sendCommandToSetUserHackMode:(BOOL) userHackMode;

/*! 
 * Initiazer that sets the mode for the robot.
 * @param deviceMode The mode to set for the robot.
 */
- (id) initToSetUserHackMode:(BOOL) userHackMode;

@end
