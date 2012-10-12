//
//  RKGetPowerStateResponse.h
//  RobotKit
//
//  Created by Brian Smith on 2/21/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceResponse.h>
#import <RobotKit/RKTypes.h>

/*! @file */


/*! @brief Response that contains state information for a robot. 
 * 
 * This response is sent to observers by RKDeviceMessenger for RKGetPowerStateResponse.
 * @sa RKGetPowerStateCommand
 * @sa RKDeviceMessenger
 */
@interface RKGetPowerStateResponse : RKDeviceResponse {
    @private
    RKBatteryPowerState powerState;
    float               batteryVoltage;
    NSUInteger          numberCharges;
    NSUInteger          timeSinceLastCharge;
}

/*! Returns an enumerated state value indicating the battery charge state. */
@property (nonatomic, readonly) RKBatteryPowerState powerState;
/*! Returns the current voltage of the robot's battery. */
@property (nonatomic, readonly) float               batteryVoltage;
/*! Returns the number of charge cycles the robot's battery has gone through. */
@property (nonatomic, readonly) NSUInteger          numberCharges;
/*! Time since the robot wake and placed in it's charger. Note: the robot needs to be awake when it 
 is placed in the charger, so the firmware can reset zero the timer. */
@property (nonatomic, readonly) NSUInteger          timeSinceLastCharge;

@end
