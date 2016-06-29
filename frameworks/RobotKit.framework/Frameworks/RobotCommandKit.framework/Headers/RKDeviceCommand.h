#import <Foundation/Foundation.h>
#import "RKDeviceMessage.h"

@interface RKDeviceCommand : RKDeviceMessage

@property (nonatomic, assign) BOOL requestsResponse;

@end
