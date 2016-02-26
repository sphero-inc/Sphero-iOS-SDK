//
//  RKSetPowerNotificationCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 8/8/12.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class used for sending set power notification commands.
 *
 * This enables Sphero to asynchronously notify the Client periodically with the power state or
 * immediately when the power manager detects a state change. Timed notifications arrive every
 * 10 seconds until they're explicitly disabled or Sphero is unpaired. This setting is volatile
 * and therefore not retained across sleep cycles.
 *
 *
 * @sa RKPowerNotificationAsyncData
 *
 */
@interface RKSetPowerNotificationCommand : RKDeviceCommand

/*! Readonly value to access the state for power notification. */
@property ( nonatomic, readonly ) BOOL state;

/*!
 * Initialize for the class that sets the state of the power notifications to
 * send to the Robot.
 * @param notificationState Set to YES to turn on power notifications, otherwise NO to
 * turn off power state notifications.
 * @return An initialized RKSetPowerNotificationCommand object.
 */
- (instancetype) initWithState:(BOOL) notificationState;

+ (instancetype) commandWithState:(bool) notificationStateEnabled;

@end
