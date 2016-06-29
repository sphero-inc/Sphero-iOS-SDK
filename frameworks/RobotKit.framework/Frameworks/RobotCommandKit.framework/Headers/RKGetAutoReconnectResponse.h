#import "RKDeviceResponse.h"

@interface RKGetAutoReconnectResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) BOOL enableFlag;
@property (nonatomic, assign, readonly) uint8_t autoReconnectStartTime;

@end
