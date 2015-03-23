//
//  RKSetBluetoothNameCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 8/8/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a request to store the robot's name.
 *
 * This command sets a UTF-8 string to be stored on the robot. The name is limited to 
 * 40 bytes. The bluetooth name is not actually changed since it does not support 
 * UTF-8 encoding.
 *
 * @sa RKSetBluetoothNameResponse
 * @sa RKGetBluetoothInfoCommand
 */
@interface RKSetBluetoothNameCommand : RKDeviceCommand

/*! The name to store on the robot. */
@property ( nonatomic, readonly ) NSString *bluetoothName;

/*!
 * Initializes an object with a name.
 * @param name A localized name to store on the robot.
 * @return The initialized object, otherwise nil if initialization failed.
 */
- (instancetype) initWithName:(NSString *) name;

@end
