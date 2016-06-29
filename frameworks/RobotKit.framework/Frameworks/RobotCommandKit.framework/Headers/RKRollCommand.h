#import "RKDeviceCommand.h"

typedef NS_ENUM(NSInteger, RKRollType) {
    RKRollStop = 0,
    RKRoll = 1,
    RKRollCalibrate = 2
};

@interface RKRollCommand : RKDeviceCommand

- (nullable instancetype)initWithHeading:(float)heading velocity:(float)velocity;
- (nullable instancetype)initWithHeading:(float)heading velocity:(float)velocity type:(RKRollType)type;
- (nullable instancetype)initWithHeading:(float)heading velocity:(float)velocity type:(RKRollType)type reverse:(BOOL)reverse;

@end