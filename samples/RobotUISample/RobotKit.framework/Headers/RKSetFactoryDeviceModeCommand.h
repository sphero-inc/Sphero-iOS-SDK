//
//  RKSetFactoryDeivceModeCommand.h
//  RobotKit
//
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceCommand.h>

/*!
 * @brief Command to assign the operation mode of Sphero.
 *
 * Command to assign the operation mode of Sphero. The user hack mode enables ASCII shell commands.
 * @sa
 */
@interface RKSetFactoryDeviceModeCommand : RKDeviceCommand {
    BOOL mode;
    UInt32 password;
}

/*!
 * Property for the mode to be set with this command.
 */
@property ( nonatomic, readonly ) BOOL mode;

/*!
 * Convience method for sending the command for a given mode.
 * @param deviceMode The mode to set for the robot.
 */
+ (void) sendCommandToSetFactoryDeviceMode:(BOOL) factoryDeviceMode password:(UInt32)pass;

/*!
 * Initiazer that sets the mode for the robot.
 * @param deviceMode The mode to set for the robot.
 */
- (id) initToSetFactoryDeviceMode:(BOOL) factoryDeviceMode password:(UInt32)pass;

@end
