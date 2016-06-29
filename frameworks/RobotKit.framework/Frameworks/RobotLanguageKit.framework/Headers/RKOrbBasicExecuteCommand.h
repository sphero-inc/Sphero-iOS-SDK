#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOrbBasicExecuteCommand : RKDeviceCommand

- (nullable instancetype)initWithStorageType:(RKOrbBasicStorageType)storageType startLine:(unsigned short)startLine;

@end
