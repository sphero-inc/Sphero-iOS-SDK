//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RobotCommandKit.h>
#import "RKMacroObject.h"

@interface RKMacroPlayer : NSObject <RKResponseObserver>

- (id)initWithRobot:(id<RKRobotBase>)robot;
- (void)play:(RKMacroObject *)macroObj;
- (void)stop;

@end
