#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOrbBasicErrorASCII : RKAsyncMessage

@property (nonatomic, strong, readonly, nonnull) NSString *error;

@end
