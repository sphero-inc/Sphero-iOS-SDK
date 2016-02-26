//
//  RKSetFactoryDeivceModeCommand.h
//  RobotCommandKit
//
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKDeviceCommand.h"

/*!
 * @brief Command to assign the operation mode of Sphero.
 *
 * Command to assign the operation mode of Sphero. The user hack mode enables ASCII shell commands.
 * @sa
 */
@interface RKSetFactoryDeviceModeCommand : RKDeviceCommand

/*!
 * Property for the mode to be set with this command.
 */
@property ( nonatomic, readonly ) uint8_t mode;

/*!
 * Initiazer that sets the mode for the robot.
 * @param deviceMode The mode to set for the robot.
 */
- (instancetype) initToSetFactoryDeviceMode:(BOOL) factoryDeviceMode password:(UInt32)pass;

@end
