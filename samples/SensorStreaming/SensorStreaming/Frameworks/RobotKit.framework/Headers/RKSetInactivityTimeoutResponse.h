//
//  RKSetInactivityTimeoutResponse.h
//  RobotKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

/*!
 * @brief A simple response to a RKSetInactivityTimeoutCommand.
 *
 * Class for the response returned for a set inactivity timeout command.
 * You can check the response code by registering an observer with RKDeviceMessenger.
 *
 * @sa RKSetInactivityTimeoutCommand
 * @sa RKDeviceMessenger
 */

@interface RKSetInactivityTimeoutResponse : RKDeviceResponse

@end
