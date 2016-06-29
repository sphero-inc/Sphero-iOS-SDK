#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t, RKConfigureLocatorFlag) {
         RKConfigureLocatorRotateWithCalibrateFlagOff = 0x00,
         RKConfigureLocatorRotateWithCalibrateFlagOn = 0x01
};

@interface RKConfigureLocatorCommand : RKDeviceCommand

- (instancetype)initForFlag:(RKConfigureLocatorFlag)flag newX:(int16_t)x newY:(int16_t)y newYaw:(int16_t)yaw;

@end
