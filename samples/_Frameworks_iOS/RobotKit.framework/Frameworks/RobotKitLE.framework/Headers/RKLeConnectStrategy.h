//
//  RKLeConnectStrategy.h
//  RobotKitLE
//
//  Created by wes on 9/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//
#import <CoreBluetooth/CoreBluetooth.h>
#import "RKLeNode.h"

@protocol RKLeConnectStrategy <NSObject>

+ (id) strategy;

-(id<RKLeNode>) nodeToConnectFromAvailableNodes:(NSArray*) availableNodes withLatestNode:(id<RKLeNode>)latestNode;

@end

