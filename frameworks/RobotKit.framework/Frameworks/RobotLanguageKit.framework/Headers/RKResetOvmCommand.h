#import <RobotCommandKit/RobotCommandKit.h>

@interface RKResetOvmCommand : RKDeviceCommand

- (nullable instancetype)initWithHardReset:(BOOL)hardReset;

@end
