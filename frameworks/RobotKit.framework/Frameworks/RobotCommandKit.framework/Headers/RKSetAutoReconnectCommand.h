#import "RKDeviceCommand.h"

@interface RKSetAutoReconnectCommand : RKDeviceCommand

- (nullable instancetype)initWithEnableFlag:(BOOL)flag startTime:(uint8_t)time;

@end
