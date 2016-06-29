#import <Foundation/Foundation.h>
#import "RKTypes.h"

@interface RKLastDataStreamingDataTracker : NSObject

+ (NSUInteger)frameCount;
+ (RKDataStreamingMask)mask;
+ (void)setFrameCount:(NSUInteger)frameCount;
+ (void)setMask:(RKDataStreamingMask)mask;

@end
