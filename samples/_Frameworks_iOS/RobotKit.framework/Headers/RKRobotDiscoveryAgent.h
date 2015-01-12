//
//  RobotDiscoveryAgent.h
//  RobotKit
//
//  Created by Corey Earwood on 11/13/14.
//  Copyright (c) 2014 orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RobotCommandKit.h>

/*!
 Discovery agent for all types of robots
 */
@interface RKRobotDiscoveryAgent : NSObject <RKDiscoveryAgent>

@property (nonatomic, assign) NSUInteger maxConnectedRobots;

+ (RKRobotDiscoveryAgent *)sharedAgent;

+ (void)disconnectAll;
- (void)disconnectAll;

- (void)addNotificationObserver:(id)observer selector:(SEL)selector;
- (void)removeNotificationObserver:(id)observer;

@end
