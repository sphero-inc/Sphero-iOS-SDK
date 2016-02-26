//
//  Copyright (c) 2014-2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKResetOvmCommand : RKDeviceCommand

- (id)initWithHardReset:(BOOL)hardReset;

@end
