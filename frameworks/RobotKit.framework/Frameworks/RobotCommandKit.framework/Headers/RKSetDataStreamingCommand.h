#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKTypes.h"

@interface RKSetDataStreamingCommand : RKDeviceCommand

- (nullable instancetype)initWithSampleRateDivisor:(uint16_t)divisor
                                     packetFrames:(uint16_t)frames
                                       sensorMask:(RKDataStreamingMask)mask
                                      packetCount:(uint8_t)count;
- (nullable instancetype)initWithStop;

@end