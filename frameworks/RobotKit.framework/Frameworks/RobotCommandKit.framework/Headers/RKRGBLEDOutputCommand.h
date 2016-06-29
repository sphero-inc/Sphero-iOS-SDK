#import "RKDeviceCommand.h"

@interface RKRGBLEDOutputCommand : RKDeviceCommand

- (nullable instancetype)initWithRed:(float)red green:(float)green blue:(float)blue;
- (nullable instancetype)initWithRed:(float)red green:(float)green blue:(float)blue userDefault:(BOOL)defaultState;

@end