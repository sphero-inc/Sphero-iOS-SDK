#import <Foundation/Foundation.h>
#import "RKAsyncMessage.h"

@interface RKAsyncFactory : NSObject

+ (nonnull instancetype)new NS_UNAVAILABLE;
+ (void)registerClass:(nonnull Class)asyncClass;
+ (nonnull RKAsyncMessage *)asyncMessageFromDeviceId:(uint8_t)deviceId commandId:(uint8_t)commandId sequenceNumber:(uint8_t)sequenceNumber data:(nullable NSData *)data requestsResponse:(BOOL)requestsResponse;

- (nonnull instancetype)init NS_UNAVAILABLE;

@end