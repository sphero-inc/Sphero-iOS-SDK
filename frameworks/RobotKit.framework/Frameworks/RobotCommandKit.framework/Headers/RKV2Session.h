#import <Foundation/Foundation.h>
#import "RKSession.h"

@interface RKV2Session : NSObject <RKSession>

@property (nonatomic, weak) id<RKSessionDelegate> delegate;

@end
