#import "RKDeviceResponse.h"
#import "RKSetNonPersistentOptionFlagsCommand.h"

@interface RKGetNonPersistentOptionFlagsResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKGetNonPersistentOptionFlagsMask optionFlags;

- (BOOL)isSetWithOptionFlag:(RKGetNonPersistentOptionFlagsMask)flag;
- (BOOL)isStopOnDisconnect;
- (BOOL)isCompatibilityModeEnabled;

@end