//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRobotBase.h"

/*! execute block when Robot connects */
typedef void (^RKRobotConnectBlock)(id<RKRobotBase> robot);


@protocol RKDiscoveryAgent <NSObject>

+(BOOL) startDiscovery;
+(BOOL) startDiscoveryAndReturnError:(NSError**) err;

+(void) stopDiscovery;

+(void) connect:(id<RKRobotBase>) robot;

+(void) connect:(id<RKRobotBase>) robot withCompletionHandler:(RKRobotConnectBlock) connectBlock;

-(BOOL) isDiscovering;

@end
