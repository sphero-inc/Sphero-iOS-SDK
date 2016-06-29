#import "RKDeviceResponse.h"

@interface RKGetPersistentPageCRCResponse : RKDeviceResponse

- (BOOL)compareCRCWithData:(NSData *)data;

@end
