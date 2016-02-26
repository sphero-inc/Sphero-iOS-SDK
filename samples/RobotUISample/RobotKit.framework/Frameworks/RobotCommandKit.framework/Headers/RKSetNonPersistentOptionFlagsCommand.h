//
//  RKSetNonPersistentOptionFlagsCommand.h
//  RobotCommandKit
//
//  Created by Jack Thorp on 8/5/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class that assigns the non-persistent option flags to the provided value and writes them to the config block.
 *  Available in Firmware 1.18 or greater
 *
 * @sa RGetNonPersistentOptionFlagsResponse for the bit definitions.
 * @sa RKSetNonPersistentOptionFlagsResponse
 */

/*! Mask values that are used to identifying what the returned bits mean */
typedef NS_OPTIONS(uint32_t,  RKGetNonPersistentOptionFlagsMask) {
   /*! Mask to force Sphero to stop on disconnect */
   RKGetNonPersistentOptionFlagsStopOnDisconnect =             0x00000001,
   /*! Mask to force Ollie to drive at speeds equivalent to Sphero */
	RKGetNonPersistentOptionFlagsCompatibilityMode =            0x00000002, // new in firmware 5.34 (ollie)
};

@interface RKSetNonPersistentOptionFlagsCommand : RKDeviceCommand

/*!
 *    Bit 0: Set to force Sphero to stop on disconnect
 *    Bit 1: Set to force Ollie to drive at speeds equivalent to Sphero
 * Bit 2-31: Reserved
 */
@property ( nonatomic, readonly ) uint32_t optionFlags;

/**
 * Initializer for setting up the object with non-persistent option flags
 * Available in Firmware 1.18 or greater
 *
 *    Bit 0: Set to force Sphero to stop on disconnect
 *    Bit 1: Set to force Ollie to drive at speeds equivalent to Sphero
 * Bit 2-31: Reserved
 *
 * @param optionFlags A long value in that represents the option flags
 */
- (instancetype) initWithOptionFlags:(uint32_t) flags;
+ (instancetype) commandWithFlags:(uint32_t) flags;

@end
