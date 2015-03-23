//
//  Copyright (c) 2014-2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"
#import <CoreBluetooth/CoreBluetooth.h>

typedef void(^RKDeviceOnlineBlock)(id<RKLeNode> node);

@protocol RKDiscoveryAgentLE <NSObject>

@optional
@property (nonatomic, assign) NSInteger maxConnectedNodes;
@property (nonatomic, strong) NSMutableSet *connectedNodes;
@property (nonatomic, strong) NSMutableSet *availableNodes;

@property (nonatomic, strong) id<RKLeConnectStrategy> connectStrategy;

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

@end


@interface RKDiscoveryAgentLE : NSObject <CBCentralManagerDelegate, RKDiscoveryAgentLE>

@property (nonatomic, assign) BOOL supportsFavorites;

- (id) initWithConnectableClass:(Class)connectableClass;
- (id) initWithConnectableClass:(Class)connectableClass andAdvertiseServiceUUIDS:(NSArray*) requiredUUIDS;

@end
