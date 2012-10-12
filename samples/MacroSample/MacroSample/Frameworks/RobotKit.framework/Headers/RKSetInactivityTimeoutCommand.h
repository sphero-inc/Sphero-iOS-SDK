//
//  RKSetInactivityTimeoutCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

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
 * @sa RKDeviceMessenger
 *
 */

@interface RKSetInactivityTimeoutCommand : RKDeviceCommand {
    uint16_t inactivityTimeout;
}

/*! Readonly value to access the length in seconds of the inactivity timeout */
@property (nonatomic, readonly) uint16_t inactivityTimeout;

/*! 
 *  Convience method that sends a command to set the inactivity timeout to the
 *  default value, which is currently 600 seconds. 
 */
+(void)sendCommand;

/*!
 * Convenience method to send a set inactivity timeout command to Sphero.
 *
 * @param timeout the length of time, in seconds, that the ball will go to sleep, if
 *                no bluetooth commands are received
 */
+(void)sendCommandWithInactivityTimeout:(uint16_t)timeout;

/*
 * Initializer to set up the set inactivity timeout command with a custom parameter
 */
-(id)initWithInactivityTimeout:(uint16_t)timeout;

@end
