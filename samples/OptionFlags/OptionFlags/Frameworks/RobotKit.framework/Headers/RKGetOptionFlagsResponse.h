//
//  RKGetOptionFlagsResponse.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"

/*! Type that is used for identifying what the returned bits mean */
typedef uint32_t RKGetOptionFlagsMask;
/*! Mask values that are used to identifying what the returned bits mean */
enum {
    /*! Mask to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth */
    RKGetOptionFlagsPreventSleepInCharger     = 0x00000001,
    /*! Mask to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued */
    RKGetOptionFlagsEnableVectorDrive         = 0x00000002,
    /*! Mask to to disable self-leveling when Sphero is inserted into the charger */
    RKGetOptionFlagsDisableSelfLevelInCharger = 0x00000004,
    /*! Mask to force the tail LED always on */
    RKGetOptionFlagsTailLightAlwaysOn         = 0x00000008,
    /*! Mask to enable motion timeouts */
    RKGetOptionFlagsEnableMotionTimeout       = 0x00000010,    
};

/*!
 * @brief Class to get option flags response, available in Firmware 1.18 or greater
 *
 *    Bit 0: Set to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth.
 *    Bit 1: Set to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued
 *           it achieves the heading before moving along it.
 *    Bit 2: Set to disable self-leveling when Sphero is inserted into the charger.
 *    Bit 3: Set to force the tail LED always on.
 *    Bit 4: Set to enable motion timeouts @see SetMotionTimeoutCommand
 * Bit 5-31: Reserved
 *
 * @see GetOptionFlagsCommand
 */

@interface RKGetOptionFlagsResponse : RKDeviceResponse {
    @private
    RKGetOptionFlagsMask optionFlags;
}

/*! The current option flags on the device */
@property (nonatomic, readonly) RKGetOptionFlagsMask optionFlags;

/*!
 * Accessor for the individual option flags properties
 *
 *    Bit 0: Set to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth.
 *    Bit 1: Set to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued
 *           it achieves the heading before moving along it.
 *    Bit 2: Set to disable self-leveling when Sphero is inserted into the charger.
 *    Bit 3: Set to force the tail LED always on.
 *    Bit 4: Set to enable motion timeouts @see SetMotionTimeoutCommand
 * Bit 5-31: Reserved
 *
 * @param flag A flag option from this class' static constants
 * @return true if the flag is set, false otherwise
 */
-(BOOL)isSetWithOptionFlag:(RKGetOptionFlagsMask)flag;

@end
