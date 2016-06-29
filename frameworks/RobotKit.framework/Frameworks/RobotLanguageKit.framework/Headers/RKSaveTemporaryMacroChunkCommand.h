#import <RobotCommandKit/RobotCommandKit.h>
#import "RKSaveTemporaryMacroCommand.h"

@interface RKSaveTemporaryMacroChunkCommand : RKDeviceCommand


- (nullable instancetype)initWithMacro:(nonnull NSData *)data flags:(RKMacroFlags)flags delay:(NSTimeInterval)delay isFirstChunk:(BOOL)isFirstChunk;

@end
