//
//  RKGetNonPersistentOptionFlagsResponse.h
//  RobotCommandKit
//
//  Created by Jack Thorp on 8/5/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"
#import "RKSetNonPersistentOptionFlagsCommand.h"

/*!
 * @brief Class to get non-persistent option flags response, available in Firmware 1.18 or greater
 *
 *    Bit 0: Set to force Sphero to stop on disconnect
 *    Bit 1: Set to force Ollie to drive at speeds equivalent to Sphero
 * Bit 2-31: Reserved
 *
 * @see RKGetNonPersistentOptionFlagsCommand
 */

@interface RKGetNonPersistentOptionFlagsResponse : RKDeviceResponse


/*! The current non-persistent option flags on the device */
@property ( nonatomic, readonly ) RKGetNonPersistentOptionFlagsMask optionFlags;

/*!
 * Accessor for the individual non-persistent option flags properties
 *
 *    Bit 0: Set to force Sphero to stop on disconnect
 *    Bit 1: Set to force Ollie to drive at speeds equivalent to Sphero
 * Bit 2-31: Reserved
 *
 * @param flag A flag option from this class' static constants
 * @return true if the flag is set, false otherwise
 */
- (BOOL) isSetWithOptionFlag:(RKGetNonPersistentOptionFlagsMask) flag;

#pragma mark - convenience methods

- (BOOL) isStopOnDisconnect;
- (BOOL) isCompatibilityModeEnabled;

@end