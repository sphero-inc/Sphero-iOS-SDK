#import "RKSaveTemporaryMacroCommand.h"
#import <RobotCommandKit/RobotCommandKit.h>

@interface RKSaveMacroCommand : RKDeviceCommand

- (nullable instancetype) initWithMacro:(nullable NSData *)data macroID:(uint8_t)identifier flags:(RKMacroFlags)flags delay:(NSTimeInterval)delay;

@end
