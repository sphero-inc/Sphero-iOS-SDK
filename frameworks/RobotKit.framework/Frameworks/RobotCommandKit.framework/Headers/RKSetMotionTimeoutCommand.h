#import "RKDeviceCommand.h"

@interface RKSetMotionTimeoutCommand : RKDeviceCommand

- (nullable instancetype)initWithTime:(uint16_t)time;

@end
