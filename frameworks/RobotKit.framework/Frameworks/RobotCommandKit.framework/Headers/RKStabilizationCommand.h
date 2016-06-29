#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t, RKStabilizationState) {
	RKStabilizationStateOff = 0,
	RKStabilizationStateOn = 1,
	RKStabilizationStateOnNoReset = 2
};

@interface RKStabilizationCommand : RKDeviceCommand

- (nullable instancetype)initWithState:(RKStabilizationState)state;

@end
