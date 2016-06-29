#import <Foundation/Foundation.h>
// Include these here so commands don't all have to declare them
#import "RKCommandList.h"
#import "RKDeviceList.h"

@interface RKDeviceMessage : NSObject

@property (nonatomic, assign, readonly) uint8_t sequenceNumber;
@property (nonatomic, strong, nullable, readonly) NSData *data;

- (uint8_t)deviceId;
- (uint8_t)commandId;

- (nullable instancetype)initWithData:(nullable NSData *)data;
- (nullable instancetype)initWithSequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data;

@end