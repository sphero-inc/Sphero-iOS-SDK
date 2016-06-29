#import "RKDeviceCommand.h"

@interface RKSetPowerNotificationCommand : RKDeviceCommand

- (instancetype)initWithState:(BOOL)notificationState;

@end
