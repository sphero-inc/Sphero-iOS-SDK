#import "RKDeviceResponse.h"
#import "RKSetOptionFlagsCommand.h"

@interface RKGetOptionFlagsResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKGetOptionFlagsMask optionFlags;

- (BOOL) isSetWithOptionFlag:(RKGetOptionFlagsMask) flag;
- (BOOL) isPreventSleepInCharger;
- (BOOL) isPreventSelfLevelInCharger;
- (BOOL) isMotionTimeout;
- (BOOL) isVectorDrive;
- (BOOL) isTailLightAlwaysOn;

@end
