//
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class that assigns the option flags to the provided value and writes them to the config block.
 *  Available in Firmware 1.18 or greater
 *
 * @sa GetOptionFlagsResponse for the bit definitions.
 * @sa RKSetOptionFlagsResponse
 */

/*! Mask values that are used to identifying what the returned bits mean */
typedef NS_OPTIONS(uint32_t,  RKGetOptionFlagsMask) {
    /*! Mask to prevent Sphero from going to sleep when placed in the charger and connected over Bluetooth */
    RKGetOptionFlagsPreventSleepInCharger = 		0x00000001,
    /*! Mask to enable Vector Drive, that is, when Sphero is stopped and a new roll command is issued */
    RKGetOptionFlagsEnableVectorDrive = 			0x00000002,
    /*! Mask to to disable self-leveling when Sphero is inserted into the charger */
    RKGetOptionFlagsDisableSelfLevelInCharger = 	0x00000004,
    /*! Mask to force the tail LED always on */
    RKGetOptionFlagsTailLightAlwaysOn = 			0x00000008,
    /*! Mask to enable motion timeouts */
    RKGetOptionFlagsEnableMotionTimeout = 			0x00000010,
	
	RKGetOptionFlagsDemoMode = 						0x00000020,
	
	RKGetOptionFlagsLightDoubleTap = 				0x00000040,
	RKGetOptionFlagsHeavyDoubleTap = 				0x00000080,
	RKGetOptionFlagsGyroMaxAsync =   				0x00000100, // new in firmware 1.47 (sphero)
	RKGetOptionFlagsEnableSoul   =   				0x00000200,
	RKGetOptionFlagsSlewRawMotors  =       			0x00000400,
};

@interface RKSetOptionFlagsCommand : RKDeviceCommand

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
@property ( nonatomic, readonly ) uint32_t optionFlags;

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
- (instancetype) initWithOptionFlags:(uint32_t) flags;
+ (instancetype) commandWithFlags:(uint32_t) flags;

@end
