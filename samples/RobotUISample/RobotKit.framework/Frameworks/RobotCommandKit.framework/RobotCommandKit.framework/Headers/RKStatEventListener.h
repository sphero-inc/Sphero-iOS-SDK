//
//  RKStatEventListener.h
//  RobotKitLE
//
//  Created by Hunter Lang on 7/14/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RKRobotBase.h>

@interface RKStatEventListener : NSObject <RKResponseObserver>

+ (instancetype)sharedListener;
- (void)startListener;
- (void)stopListener;


@end
