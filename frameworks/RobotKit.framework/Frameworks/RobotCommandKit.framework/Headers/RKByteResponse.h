#import "RKDeviceResponse.h"

@interface RKByteResponse : RKDeviceResponse

- (nullable instancetype)initWithResponseCode:(RKResponseCode)responseCode andData:(nullable NSData *)data NS_UNAVAILABLE;
- (nullable instancetype)initWithResponseCode:(RKResponseCode)responseCode sequenceNumber:(uint8_t)sequenceNumber deviceId:(uint8_t)deviceId commandId:(uint8_t)commandId data:(nullable NSData *)data;

@end
