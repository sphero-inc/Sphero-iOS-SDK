//
//  RKWatchDiscoveryAgent.h
//  RobotKitLE
//
//  Created by Paul Trebilcox on 11/9/15.
//  Copyright © 2015 Sphero. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

typedef void(^RKIsConnectedToWearableCallback)(BOOL isWearableConnected);

@interface RKAccessoryDiscoveryAgent : NSObject

- (void)isWearableConnectedWith:(RKIsConnectedToWearableCallback)callback;

@end
