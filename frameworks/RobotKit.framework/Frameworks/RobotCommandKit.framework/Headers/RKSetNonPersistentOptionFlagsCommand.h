#import "RKDeviceCommand.h"

typedef NS_OPTIONS(uint32_t,  RKGetNonPersistentOptionFlagsMask) {
   RKGetNonPersistentOptionFlagsStopOnDisconnect = 0x00000001,
	RKGetNonPersistentOptionFlagsCompatibilityMode = 0x00000002,
};

@interface RKSetNonPersistentOptionFlagsCommand : RKDeviceCommand

- (instancetype) initWithOptionFlags:(uint32_t)flags;

@end
