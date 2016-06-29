#import "RobotCommandKit.h"

@interface RKReadOdometerResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) uint32_t distanceInCentimeters;

@end
