#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t, RKSleepType) {
    RKSleep = 0x00,
    RKSleepDeep = 0x01,
    RKSleepLowPower = 0x02
};

typedef uint16_t RKSleepTimeInterval;

@interface RKGoToSleepCommand : RKDeviceCommand

- (nullable instancetype)initWithWakeUpTimeInterval:(RKSleepTimeInterval)interval macroId:(uint8_t)identifier;
- (nullable instancetype)initWithWakeUpTimeInterval:(RKSleepTimeInterval)interval orbbasic:(uint16_t)lineNumber;

@end
