//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import "RKDeviceResponse.h"
#import "RKTypes.h"

/*! @file */


/*! @brief Response that contains state information for a robot. 
 * 
 * @sa RKGetPowerStateCommand
 */

@interface RKGetPowerStateResponse : RKDeviceResponse

/*! Returns an enumerated state value indicating the battery charge state. */
@property ( nonatomic, readonly ) RKBatteryPowerState powerState;

/*! Returns the current voltage of the robot's battery. */
@property ( nonatomic, readonly ) float batteryVoltage;

/*! Returns the number of charge cycles the robot's battery has gone through. */
@property ( nonatomic, readonly ) NSUInteger numberCharges;

/*! Time since the robot wake and placed in it's charger. Note: the robot needs to be awake when it 
 is placed in the charger, so the firmware can reset zero the timer. 
 Seconds awake since last recharge (unsigned 16-bit value) */
@property ( nonatomic, readonly ) NSUInteger timeSinceLastCharge;

@end
