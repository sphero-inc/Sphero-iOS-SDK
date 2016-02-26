//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

/*! @see RKGetPowerStateResponse - provides more details. */
@interface RKGetChargerStateResponse : RKDeviceResponse

/*! Returns an enumerated state value indicating the battery charge state. */
@property ( nonatomic, readonly ) RKBatteryPowerState batteryState;

@property (readonly) RKChargerState chargerState;

@end
