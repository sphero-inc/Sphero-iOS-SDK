//
//  RKSelfLevelCompleteAsyncData.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/14/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceAsyncData.h"

typedef NS_ENUM(uint8_t, RKSelfLevelCompleteResultCode ) {
   /*! The result byte can be: 00h = Unknown */
         RKSelfLevelCompleteResultCodeUnknown = 0x00,
   /*! 01h = Timed Out (level was not achieved) */
         RKSelfLevelCompleteResultCodeTimeOut = 0x01,
   /*! 02h = Sensors Error */
         RKSelfLevelCompleteResultCodeSensorsError = 0x02,
   /*! 03h = Self Level Disabled (see Option Flags) */
         RKSelfLevelCompleteResultCodeSelfLevelDisable = 0x03,
   /*! 04h = Aborted (by API call) */
         RKSelfLevelCompleteResultCodeAborted = 0x04,
   /*! 05h = Charget not found */
         RKSelfLevelCompleteResultCodeChargerNotFound = 0x05,
   /*! 06h = Success */
         RKSelfLevelCompleteResultCodeSuccess = 0x06
};


/*!
 * @brief Class to represent the aync response after teh self level command has completed
 *
 * Async data packet sent when Device is done self leveling.  
 * Use the RKSelfLevelCompleteResultCode enum to determine the result of the command.
 *
 * @sa RKSelfLevelCommand
 *
 */
@interface RKSelfLevelCompleteAsyncData : RKAsyncMessage

/* Results code */
@property ( nonatomic, readonly ) RKSelfLevelCompleteResultCode resultCode;

@end
