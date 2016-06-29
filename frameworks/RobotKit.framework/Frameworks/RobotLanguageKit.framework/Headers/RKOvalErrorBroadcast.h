#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOvalErrorBroadcast : RKAsyncMessage

@property (nonatomic, assign, readonly) int errorCode;

- (nonnull NSString *)errorDescription;

@end
