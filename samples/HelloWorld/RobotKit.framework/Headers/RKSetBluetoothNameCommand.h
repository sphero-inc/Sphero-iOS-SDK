//
//  RKSetBluetoothNameCommand.h
//  RobotKit
//
//  Created by Brian Smith on 8/8/11.
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
@interface RKSetBluetoothNameCommand : RKDeviceCommand {
   NSString *bluetoothName;
}

/*! The name to store on the robot. */
@property ( nonatomic, readonly ) NSString *bluetoothName;

/*!
 * Convenience method that sends a new name to be stored on the robot.
 * @param name A new name to store on the robot.
 */
+ (void) sendCommandWithName:(NSString *) name;
/*!
 * Initializes an object with a name.
 * @param name A localized name to store on the robot.
 * @return The initialized object, otherwise nil if initialization failed.
 */
- (id) initWithName:(NSString *) name;

@end
