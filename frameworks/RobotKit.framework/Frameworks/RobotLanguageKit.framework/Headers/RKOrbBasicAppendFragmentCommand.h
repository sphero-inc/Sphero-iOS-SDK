#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOrbBasicAppendFragmentCommand : RKDeviceCommand

- (nullable instancetype)initWithStorageType:(RKOrbBasicStorageType)type fragment:(nonnull NSData *)frag;

@end
