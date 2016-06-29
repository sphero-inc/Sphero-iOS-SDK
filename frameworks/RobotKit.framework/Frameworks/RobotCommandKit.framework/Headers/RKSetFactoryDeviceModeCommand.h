#import "RKDeviceCommand.h"

@interface RKSetFactoryDeviceModeCommand : RKDeviceCommand

- (nullable instancetype)initWithFactoryModeRequest:(BOOL)factoryDeviceMode password:(UInt32)pass;

@end
