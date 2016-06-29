#import "RKDeviceCommand.h"

typedef NS_OPTIONS(uint32_t,  RKGetOptionFlagsMask) {
    RKGetOptionFlagsPreventSleepInCharger = 		0x00000001,
    RKGetOptionFlagsEnableVectorDrive = 			0x00000002,
    RKGetOptionFlagsDisableSelfLevelInCharger = 	0x00000004,
    RKGetOptionFlagsTailLightAlwaysOn = 			0x00000008,
    RKGetOptionFlagsEnableMotionTimeout = 			0x00000010,
	RKGetOptionFlagsDemoMode = 						0x00000020,
    RKGetOptionFlagsLightDoubleTap = 				0x00000040,
	RKGetOptionFlagsHeavyDoubleTap = 				0x00000080,
	RKGetOptionFlagsGyroMaxAsync =   				0x00000100,
	RKGetOptionFlagsEnableSoul   =   				0x00000200,
	RKGetOptionFlagsSlewRawMotors  =       			0x00000400,
};

@interface RKSetOptionFlagsCommand : RKDeviceCommand

- (nullable instancetype)initWithOptionFlags:(uint32_t)flags;

@end
