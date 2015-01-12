//
//  RKConnectableNotification.h
//  RobotKitLE
//
//  Created by Corey Earwood on 10/13/14.
//  Copyright (c) 2014-2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"
#import <RobotCommandKit/RobotCommandKit.h>

FOUNDATION_EXPORT NSString *const kNodeAvailableNotification;

// these enum values must match RKRobotStateChangeNotificationType
typedef NS_ENUM(uint8_t, RKNodeState) {
	/*! requested a connection to the Node */
	RKNodeConnecting = RKRobotConnecting,
	
	/*! Radio Connected */
	RKNodeConnected = RKRobotConnected,

	/*! connected & ready for action */
	RKNodeOnline = RKRobotOnline,

	/*! node is offline, but radio could still be connected */
	RKNodeOffline = RKRobotOffline,

	/*! Radio Disconnected */
	RKNodeDisconnected = RKRobotDisconnected,

	/*! Duh. */
	RKNodeFailedConnect = RKRobotFailedConnect
};

@interface RKNodeStateChangedNotification : NSObject

@property (nonatomic, strong, readonly) id<RKLeNode>node;
@property (nonatomic, assign, readonly) RKNodeState type;

+(id)notificationWithNode:(id<RKLeNode>)node andType:(RKNodeState)type;

-(NSString*) stringTypeValue;

@end

@interface RKNodeAvailableNotification : NSNotification

@property (nonatomic, strong, readonly) NSArray *nodes;
@property (nonatomic, strong, readonly) id<RKLeNode> node;

+(id)notificationWithNode:(id<RKLeNode>)node andWithNodes:(NSArray *)nodes andNodeClass:(Class)nodeClass;

@end

@interface RKNodeStateChangeObserver : NSObject

@property (nonatomic, weak, readonly) id observer;
@property (nonatomic, assign, readonly) SEL selector;

+(id)observer:(id)observer withSelector:(SEL)selector;

@end
