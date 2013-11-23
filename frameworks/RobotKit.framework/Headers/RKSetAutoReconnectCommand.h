//
//  RKSetAutoReconnectCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 9/4/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

/*!
 * @brief Class used for sending set auto reconnect commands.
 *
 * This configures the control of the Bluetooth module in its attempt to automatically 
 * reconnect with the last mobile Apple device. This is a courtesy behavior since the 
 * Apple Bluetooth stack doesn't initiate automatic reconnection on its own.
 *
 * The two parameters are simple: flag is 00h to disable or 01h to enable, 
 * and time is the number of seconds after power-up in which to enable auto 
 * reconnect mode. For example, if time = 30 then the module will be attempt 
 * reconnecting 30 seconds after waking up. (refer to RN-APL-EVAL pg. 7 for more info)
 *
 * @sa RKSetAutoReconnectResponse
 * @sa RKDeviceMessenger
 *
 */

@interface RKSetAutoReconnectCommand : RKDeviceCommand {
    BOOL    enableFlag;
    uint8_t autoReconnectStartTime;
}

/*! Readonly value to access the enable flag for the command */
@property (nonatomic, readonly) BOOL    enableFlag;
/*! Readonly value to access the start time of the auto reconnect state */
@property (nonatomic, readonly) uint8_t autoReconnectStartTime;

/*!
 *  Convience method that sends a command to set the auto reconnect to the
 *  default values, which is enabled and time of 0 seconds.
 */
+(void)sendCommand;

/*!
 * Convenience method to send a set auto reconnect command to Sphero.
 *
 * @param flag YES to enable auto reconnect, NO to disable it
 *
 * @param time the length of time, in seconds, that passes after Sphero is shaken awake
 *             before it attempts to auto reconnect
 */
+(void)sendCommandWithEnableFlag:(BOOL)flag StartTime:(uint8_t)time;

/*
 * Initializer to set up the set auto reconnect command with custom parameters
 * 
 * @param flag YES to enable auto reconnect, NO to disable it
 *
 * @param time the length of time, in seconds, that passes after Sphero is shaken awake
 *             before it attempts to auto reconnect
 */
-(id)initWithEnableFlag:(BOOL)flag StartTime:(uint8_t)time;

@end
