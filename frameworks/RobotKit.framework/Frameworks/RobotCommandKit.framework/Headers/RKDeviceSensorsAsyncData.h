#import "RKAsyncMessage.h"

@interface RKDeviceSensorsAsyncData : RKAsyncMessage

@property (nonatomic, strong, readonly) NSArray *dataFrames;

@end
