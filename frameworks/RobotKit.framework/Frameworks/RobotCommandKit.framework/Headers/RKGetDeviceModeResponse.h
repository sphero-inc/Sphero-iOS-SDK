#import "RKDeviceResponse.h"

typedef NS_ENUM(uint8_t, RKDeviceMode) {
	RKDeviceModeNormal = 0,
	RKDeviceModeUserHack = 1,
	RKDeviceModeFactory = 2
};

@interface RKGetDeviceModeResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKDeviceMode mode;

@end
