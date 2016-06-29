#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOvalDeviceBroadcast : RKAsyncMessage

@property (nonatomic, strong, nonnull) NSArray *floats;
@property (nonatomic, strong, nonnull) NSArray *ints;

- (nonnull NSString *)stringInterpretation;

@end
