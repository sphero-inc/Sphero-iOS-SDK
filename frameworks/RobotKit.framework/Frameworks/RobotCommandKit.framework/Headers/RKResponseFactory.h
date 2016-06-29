#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKDeviceResponse.h"

@interface RKResponseFactory : NSObject

+ (nonnull instancetype)new NS_UNAVAILABLE;
+ (void)registerResponse:(nonnull Class)responseClass;
+ (nonnull RKDeviceResponse *)responseFromDeviceId:(uint8_t)deviceId
                                         commandId:(uint8_t)commandId
                                    sequenceNumber:(uint8_t)sequenceNumber
                                      responseCode:(uint8_t)responseCode
                                              data:(nonnull NSData *)data;

- (nonnull instancetype)init NS_UNAVAILABLE;

@end
