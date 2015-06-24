//
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

+ (BOOL) startDiscoveryAndReturnError:(NSError **) error;
- (BOOL) startDiscoveryAndReturnError:(NSError **) error;
- (void)stopDiscovery;

+ (void)disconnectAll;
- (void)disconnectAll;

- (void)addNotificationObserver:(id)observer selector:(SEL)selector;
- (void)removeNotificationObserver:(id)observer;

- (NSOrderedSet*) connectingRobots;
- (NSOrderedSet*) connectedRobots;
- (NSOrderedSet*) onlineRobots;

- (BOOL) isDiscovering;


@end
