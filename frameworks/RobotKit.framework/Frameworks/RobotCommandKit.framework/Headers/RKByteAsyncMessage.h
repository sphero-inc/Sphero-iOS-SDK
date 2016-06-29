#import "RKAsyncMessage.h"

@interface RKByteAsyncMessage : RKAsyncMessage

- (nullable instancetype)initWithSequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data NS_UNAVAILABLE;
- (nullable instancetype)initWithRequestsResponse:(BOOL)requestsResponse deviceId:(uint8_t)deviceId commandId:(uint8_t)commandId sequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data;

@end
