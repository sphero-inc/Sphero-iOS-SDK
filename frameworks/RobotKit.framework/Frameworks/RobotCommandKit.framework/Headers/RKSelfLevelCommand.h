#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t,  RKSelfLevelCommandOptions) {
         RKSelfLevelCommandOptionStart = 0x01,
         RKSelfLevelCommandOptionKeepHeading = 0x02,
         RKSelfLevelCommandOptionSleepAfter = 0x04,
         RKSelfLevelCommandOptionControlSystemOn = 0x08
};

@interface RKSelfLevelCommand : RKDeviceCommand

- (nullable instancetype)initWithOptions:(RKSelfLevelCommandOptions)options
                              angleLimit:(uint8_t)angleLimit
                                 timeout:(uint8_t)timeout
                                accuracy:(uint8_t)accuracy;

@end
