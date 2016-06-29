#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOrbBasicEraseStorageCommand : RKDeviceCommand

- (nullable instancetype)initWithStorageType:(RKOrbBasicStorageType)storage;

@end
