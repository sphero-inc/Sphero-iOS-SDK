#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKAsyncMessage.h"
#import "RKDeviceCommand.h"
#import "RKSession.h"

@interface RKV1Session : NSObject <RKSession>

@property (nonatomic, weak) id<RKSessionDelegate> delegate;

@end
