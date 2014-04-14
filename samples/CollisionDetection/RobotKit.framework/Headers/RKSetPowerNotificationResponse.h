//
//  RKSetPowerNotificationResponse.h
//  RobotKit
//
//  Created by Brian Smith on 8/8/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//


#import <RobotKit/RKDeviceResponse.h>

/*! @file */

/*!
 * @brief A simple response to a RKSetPowerNotificationCommand. 
 * 
 * Class for the response returned for a set power notification command. You can check the response code by
 * registering an observer with RKDeviceMessenger.
 *
 * @sa RKSetPowerNotificationCommand
 * @sa RKDeviceMessenger
 */
@interface RKSetPowerNotificationResponse : RKDeviceResponse

@end
