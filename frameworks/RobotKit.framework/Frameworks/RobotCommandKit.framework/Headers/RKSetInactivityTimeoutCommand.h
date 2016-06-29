#import "RKDeviceCommand.h"

@interface RKSetInactivityTimeoutCommand : RKDeviceCommand

- (nullable instancetype)initWithInactivityTimeout:(uint16_t)timeout;

@end
