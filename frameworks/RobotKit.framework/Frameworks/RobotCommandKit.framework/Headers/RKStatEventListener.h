//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RKRobotBase.h>

@interface RKStatEventListener : NSObject <RKResponseObserver>

+ (instancetype)sharedListener;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (void)startListener;
- (void)stopListener;


@end
