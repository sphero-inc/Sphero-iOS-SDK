#import "RKAsyncMessage.h"
#import "RKTypes.h"

@interface RKPowerNotificationAsyncData : RKAsyncMessage

@property ( nonatomic, readonly ) RKBatteryPowerState state;

@end
