#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t, RKRawMotorMode) {
	RKRawMotorModeOff = 0,
	RKRawMotorModeForward = 1,
	RKRawMotorModeReverse = 2,
	RKRawMotorModeBrake = 3,
	RKRawMotorModeIgnore = 4
};

typedef uint8_t RKRawMotorPower;

@interface RKRawMotorValuesCommand : RKDeviceCommand

- (nullable instancetype)initWithLeftMode:(RKRawMotorMode)leftMode
                               leftPower:(RKRawMotorPower)leftPower
                               rightMode:(RKRawMotorMode)rightMode
                              rightPower:(RKRawMotorPower)rightPower;

@end