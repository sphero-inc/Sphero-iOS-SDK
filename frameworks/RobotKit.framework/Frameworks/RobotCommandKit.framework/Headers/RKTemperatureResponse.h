#import "RKDeviceResponse.h"

@interface RKTemperatureResponse : RKDeviceResponse

@property (nonatomic, strong, readonly) NSNumber *temperature;

@end
