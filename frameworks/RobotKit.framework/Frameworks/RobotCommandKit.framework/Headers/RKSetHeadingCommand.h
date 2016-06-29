#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

@interface RKSetHeadingCommand : RKDeviceCommand

- (nullable instancetype)initWithHeading:(uint16_t)heading;

@end