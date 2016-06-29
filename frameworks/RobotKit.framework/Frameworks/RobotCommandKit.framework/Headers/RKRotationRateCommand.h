#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

@interface RKRotationRateCommand : RKDeviceCommand

- (nullable instancetype)initWithRate:(float)rate;

@end