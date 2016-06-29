#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOrbBasicPrintMessage : RKAsyncMessage

@property (nonatomic, strong, readonly, nonnull) NSString *message;

@end
