#import "RKDeviceResponse.h"
#import "RKTypes.h"

@interface RKGetChargerStateResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKBatteryPowerState batteryState;
@property (nonatomic, assign, readonly) RKChargerState chargerState;

@end
