#import "RKDeviceResponse.h"

@interface RKGetSkuResponse : RKDeviceResponse

@property (nonatomic, strong, readonly) NSString *sku;

- (BOOL)isDarkside;

@end
