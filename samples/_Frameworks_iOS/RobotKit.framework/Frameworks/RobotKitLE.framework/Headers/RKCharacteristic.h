//
//  RKCharacteristic.h
//  RobotKitLE
//
//  Created by wes on 11/22/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface RKCharacteristic : NSObject

@property (strong, nonatomic, readonly) CBCharacteristic* characteristic;
@property (readwrite) BOOL waitOnResponse;


@end
