//
//  Copyright (c) 2014-2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"
#import "RKRobotRadioDescriptor.h"
#import <CoreBluetooth/CoreBluetooth.h>

typedef void(^RKDeviceOnlineBlock)(id<RKLeNode> node);

@protocol RKDiscoveryAgentLE <NSObject>

@optional
@property (nonatomic, assign) NSInteger maxConnectedNodes;
@property (nonatomic, strong) NSMutableOrderedSet *availableNodes;
@property (nonatomic, strong) id<RKLeConnectStrategy> connectStrategy;

- (NSOrderedSet*) connectingNodes;
- (NSOrderedSet*) connectedNodes;
- (NSOrderedSet*) onlineNodes;

-(BOOL) startDiscovery;
-(BOOL) startDiscoveryAndReturnError:(NSError **) error;
-(void) stopDiscovery;
-(void) disconnectAll;

/*!
 @param observer
 The observing object
 @param selector
 A selector that takes single RKNodeStateChangedNotification parameter
 i.e. -(void)stateChanged:(RKNodeStateChangedNotification *)notification
 */
-(void)addNotificationObserver:(id)observer selector:(SEL)selector;
-(void)removeNotificationObserver:(id)observer;
-(BOOL)isLEEnabled;
-(void)connect:(id<RKLeNode>)node;
-(void)disconnect:(id<RKLeNode>)node;

- (id) nodeForName:(NSString*) name;

/*! Experimental - internal use only */
-(void)connect:(id<RKLeNode>)node withCompletionHandler:(RKDeviceOnlineBlock)completionHandler;

@required
-(void) setRadioDescriptor:(RKRadioDescriptor*) radioDescriptor;

@end


/*! Node agnostic BLE Discovery Agent */
@interface RKDiscoveryAgentLE : NSObject <CBCentralManagerDelegate, RKDiscoveryAgentLE>

@property (nonatomic, assign) BOOL supportsFavorites;

- (id) initWithConnectableClass:(Class)connectableClass andRadioDescriptor:(RKRadioDescriptor*) descriptor;

- (BOOL) isDiscovering;


@end
