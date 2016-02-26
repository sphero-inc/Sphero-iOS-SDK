//
//  RKSetInactivityTimeoutCommand.h
//  RobotCommandKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class used for sending set inactivity timeout commands.
 *
 * To save battery power, Sphero normally goes to sleep after a period of inactivity. 
 * From the factory this value is set to 600 seconds (10 minutes) but this API command 
 * can alter it to any value of 60 seconds or greater.
 *
 * The inactivity timer is reset every time an API command is received over Bluetooth 
 * or a shell command is executed in User Hack mode. In addition, the timer is 
 * continually reset when a macro is running unless the MF_STEALTH flag is set, 
 * and the same for orbBasic unless the BF_STEALTH flag is set.
 *
 * @sa RKSetInactivityTimeoutResponse
 *
 */

@interface RKSetInactivityTimeoutCommand : RKDeviceCommand

/*! Readonly value to access the length in seconds of the inactivity timeout */
@property ( nonatomic, readonly ) uint16_t inactivityTimeout;

/*
 * Initializer to set up the set inactivity timeout command with a custom parameter
 */
- (instancetype) initWithInactivityTimeout:(uint16_t) timeout;

@end
