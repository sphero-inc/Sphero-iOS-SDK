//
//  RKSetOptionFlagsCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"
#import "RKGetOptionFlagsResponse.h"

/*!
 * @brief Class that assigns the option flags to the provided value and writes them to the config block.
 *  Available in Firmware 1.18 or greater
 *
 * @sa GetOptionFlagsResponse for the bit definitions.
 * @sa RKSetOptionFlagsResponse
 */

@interface RKSetOptionFlagsCommand : RKDeviceCommand {
    @private
    uint32_t optionFlags;
}

/*!    
 *    Bit 0: Set to prevent Sphero from going to sleep when placed in the 
 *           charger and connected over Bluetooth.
 *    Bit 1: Set to enable Vector Drive, that is, when Sphero is stopped and a new 
 *           roll command is issued it achieves the heading before moving along it.
 *    Bit 2: Set to disable self-leveling when Sphero is inserted into the charger.
 *    Bit 3: Set to force the tail LED always on.
 *    Bit 4: Set to enable motion timeouts (see DID 02h, CID 34h)
 * Bit 5-31: Reserved
*/
@property (nonatomic, readonly) uint32_t optionFlags;

/**
 * Initializer for setting up the object with option flags
 * Available in Firmware 1.18 or greater
 *
 *    Bit 0: Set to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth.
 *    Bit 1: Set to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued
 *           it achieves the heading before moving along it.
 *    Bit 2: Set to disable self-leveling when Sphero is inserted into the charger.
 *    Bit 3: Set to force the tail LED always on.
 *    Bit 4: Set to enable motion timeouts (see DID 02h, CID 34h)
 * Bit 5-31: Reserved
 *
 * @param optionFlags A long value in that represents the option flags
 */
- (id)initWithOptionFlags:(uint32_t)flags;

/**
 * A convenience method that sends a command to a robot to return to default option flags.
 * Available in Firmware 1.18 or greater
 *
 * Defaults:
 *
 *    Bit 0: Off
 *    Bit 1: On (Vector Drive Enabled)
 *    Bit 2: Off
 *    Bit 3: Off
 *    Bit 4: Off
 *
 * Bit 5-31: Reserved
 */
+(void) sendCommand;

/**
 * A convenience method that sends a command to a robot.
 * Available in Firmware 1.18 or greater
 *
 *    Bit 0: Set to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth.
 *    Bit 1: Set to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued
 *           it achieves the heading before moving along it.
 *    Bit 2: Set to disable self-leveling when Sphero is inserted into the charger.
 *    Bit 3: Set to force the tail LED always on.
 *    Bit 4: Set to enable motion timeouts (see DID 02h, CID 34h)
 * Bit 5-31: Reserved
 *
 * @param optionFlags A long value in that represents the option flags
 */
+ (void)sendCommandWithOptionFlags:(uint32_t)flags;

@end
