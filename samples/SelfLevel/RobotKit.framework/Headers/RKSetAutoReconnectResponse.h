//
//  RKSetAutoReconnectResponse.h
//  RobotKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

/*!
 * @brief A simple response to a RKSetAutoReconnectCommand.
 *
 * Class for the response returned for a set auto reconnect command.
 * You can check the response code by registering an observer with RKDeviceMessenger.
 *
 * @sa RKSetAutoReconnectCommand
 * @sa RKDeviceMessenger
 */

@interface RKSetAutoReconnectResponse : RKDeviceResponse

@end
