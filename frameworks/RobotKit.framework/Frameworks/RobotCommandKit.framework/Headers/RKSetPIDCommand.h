#import "RKDeviceCommand.h"

typedef NS_ENUM(Byte, RKAxis){
	RKPitchAxis = 0x00,
	RKRollAxis = 0x01,
	RKYawAxis = 0x02
};

@interface RKSetPIDCommand : RKDeviceCommand

- (nullable instancetype)initWithAxis:(RKAxis)axis p:(nonnull NSNumber *)p i:(nonnull NSNumber *)i andD:(nonnull NSNumber *)d;

@end