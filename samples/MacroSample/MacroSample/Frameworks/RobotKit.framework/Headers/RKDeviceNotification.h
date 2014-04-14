//
//  RKDeviceNotification.h
//  RobotKit
//
//  Created by Michael DePhillips on 1/14/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>

/*! Type that is used for accessing the notification type of the device message */
typedef int RKDeviceNotificationType;
enum {
   /*! The robot successfully connected */
         RKDeviceNotificationTypeConnected = 0,
   /*! The robot disconnected */
         RKDeviceNotificationTypeDisconnected = 1,
   /*! The robot connection attempt failed */
         RKDeviceNotificationTypeConnectionFailed = 2,
   /*! The robot has become available */
        RKDeviceNotificationTypeAvailable = 3,
   
        RKDeviceNotificationTypeMainAppCorrupt = 4
};


/*!
 * @brief Class that contains the notification type for a Device Message
 *
 * @sa RKDeviceMessege
 */
@interface RKDeviceNotification : RKDeviceMessage {
   RKDeviceNotificationType type;
}

/*! The type of notification from the robot */
@property ( nonatomic, readonly ) RKDeviceNotificationType type;

/*! Constructor to set the notification type */
- (id) initWithNotificationType:(RKDeviceNotificationType) notificationType;

@end
