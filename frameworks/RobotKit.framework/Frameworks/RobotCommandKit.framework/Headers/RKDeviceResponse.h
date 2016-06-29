#import <Foundation/Foundation.h>
#import "RKDeviceMessage.h"
#import "RKResponseCodes.h"

@interface RKDeviceResponse : RKDeviceMessage

@property (nonatomic, assign, readonly) RKResponseCode responseCode;

- (nullable instancetype)initWithSequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data NS_UNAVAILABLE;
- (nullable instancetype)initWithSequenceNumber:(uint8_t)sequenceNumber responseCode:(RKResponseCode)responseCode data:(nullable NSData *)data;

@end
