#import <RobotCommandKit/RobotCommandKit.h>

typedef NS_OPTIONS(uint8_t, RKMacroFlags) {
    RKMacroFlagNone = 0x0000,
    RKMacroFlagMotorControl = 0x0001,
    RKMacroFlagExclusiveDrive = 0x0002,
    RKMacroFlagUseVersion3 = 0x0004,
    RKMacroFlagInhibitIfConnected = 0x0008,
    RKMacroFlagEndMarker = 0x0010,
    RKMacroFlagStealth = 0x0020,
    RKMacroFlagUnkillable = 0x0040,
    RKMacroFlagExtendedFlags = 0x0080
};

@interface RKSaveTemporaryMacroCommand : RKDeviceCommand

- (nullable instancetype)initWithMacro:(nullable NSData *)data flags:(RKMacroFlags)flags delay:(NSTimeInterval)delay;

@end
