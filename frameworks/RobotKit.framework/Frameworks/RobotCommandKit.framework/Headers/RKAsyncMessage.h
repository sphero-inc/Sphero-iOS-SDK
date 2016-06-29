#import "RKDeviceCommand.h"
#import "RKAsyncId.h"

@interface RKAsyncMessage : RKDeviceCommand

- (nullable instancetype)initWithSequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data NS_DESIGNATED_INITIALIZER;

- (RKAsyncId)asyncId;

@end
