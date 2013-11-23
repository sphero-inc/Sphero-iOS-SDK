//
//  RKSetMotionTimeoutCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 *  @brief Class encapsulates a way to set the ultimate timeout for the last motion command to keep Sphero from
 *  rolling away in the case of a crashed (or paused) client app.
 *  The timeBeforeTimeout parameter is expressed in milliseconds and default to 2000 upon wake-up.
 *
 *  If the control system is enabled, the timeout triggers a stop otherwise it commands zero PWM to both motors.
 *  This "termination behavior" is inhibited if a macro is running with the flag MF_EXCLUSIVE_DRV set,
 *  or an orbBasic program is executing with a similar flag, BF_EXCLUSIVE_DRV.
 *
 *  Note that you must enable this action by setting System Option Flag #4.
 *  Available in Firmware 1.18 or greater
 *
 *  @sa RKSetOptionFlagsCommand
 *  @sa RKSetMotionTimeoutResponse
 */

@interface RKSetMotionTimeoutCommand : RKDeviceCommand {
    @private
    uint16_t timeBeforeTimeout;
}

/*! The brightness value between 0.0 to 1.0 where 0.0 is off and 1.0 is full brightness. */
@property (nonatomic, readonly) uint16_t timeBeforeTimeout;

/*! 
 * A convenience method for sending the command to the device.
 * Available in Firmware 1.18 or greater
 * @param time The time length in (ms) that Sphero will stop rolling if you don't send another roll command
 *             This value defaults to 2000 ms
 */
+ (void)sendCommandWithTime:(uint16_t)time;

/*! 
 * A convenience method for sending the command to the device, makes the default time 2000 ms
 * Available in Firmware 1.18 or greater
 */
+ (void)sendCommand;

/*! 
 * Initializer for a object.
 * Available in Firmware 1.18 or greater
 * @param time The time length in (ms) that Sphero will stop rolling if you don't send another roll command
 *             This value defaults to 2000 ms
 * @return The initialized object.
 */
- (id)initWithTime:(uint16_t)time;

@end
