//
//  RKGetAutoReconnectCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

/*!
 * @brief Class used for sending get auto reconnect commands.
 *
 * This returns the Bluetooth auto reconnect values as defined in the 
 * “Set Auto Reconnect” command.
 *
 * @sa RKSetAutoReconnectCommand
 * @sa RKGetAutoReconnectResponse
 * @sa RKDeviceMessenger
 *
 */

@interface RKGetAutoReconnectCommand : RKDeviceCommand

@end
