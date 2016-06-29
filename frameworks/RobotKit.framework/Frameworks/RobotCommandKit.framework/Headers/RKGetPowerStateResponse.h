#import "RKDeviceResponse.h"
#import "RKTypes.h"

@interface RKGetPowerStateResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKBatteryPowerState powerState;
@property (nonatomic, assign, readonly) float batteryVoltage;
@property (nonatomic, assign, readonly) NSUInteger numberCharges;
@property (nonatomic, assign, readonly) NSUInteger timeSinceLastCharge;

@end
