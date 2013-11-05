//
//  RKPowerNotificationAsyncData.h
//  RobotKit
//
//  Created by Brian Smith on 8/8/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//


#import <RobotKit/RKDeviceAsyncData.h>
#import <RobotKit/RKTypes.h>

/*! @file */

/*!
 * @brief Class for asynchronous power notification messages.
 *
 * To enable these notification, use the RKSetPowerNotificationCommand to initiate the notifications.
 * The robot will send the notifications at intervals of 10 seconds with the battery state. The notification
 * is received in client code by registering as an observer for data streaming events. 
 * 
 * @sa RKSetPowerNotificationCommand
 * @sa RKDeviceMessenger
 */
@interface RKPowerNotificationAsyncData : RKDeviceAsyncData {
@private
   RKBatteryPowerState state;
}

/*! Readonly property for the power state for the notification. */
@property ( nonatomic, readonly ) RKBatteryPowerState state;

@end
