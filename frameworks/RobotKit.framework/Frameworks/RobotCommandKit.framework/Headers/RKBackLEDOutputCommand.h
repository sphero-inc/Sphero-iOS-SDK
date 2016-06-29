#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

@interface RKBackLEDOutputCommand : RKDeviceCommand

- (nullable instancetype)initWithBrightness:(float)brightness;

@end
