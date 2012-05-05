//
//  RKSleepNotificationAsyncData.h
//  RobotKit
//
//  Created by Brian Smith on 10/17/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceAsyncData.h"

/*!
 * @brief Class that represents an asychronous sleep notification sent from a Sphero.
 * 
 * Class that represents an asychronous sleep notification, which is sent from Sphero 10
 * seconds before it goes to sleep. To receive this object, clients register as asyncronous data 
 * observers with the RKDeviceMessenger singleton.
 *
 * @sa RKDeviceMessenger
 */
@interface RKSleepNotificationAsyncData : RKDeviceAsyncData 
@end
