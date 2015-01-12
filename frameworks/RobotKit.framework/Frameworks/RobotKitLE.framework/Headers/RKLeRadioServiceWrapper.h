//
//  RKLeRadioServiceWrapper.h
//  RobotKitLE
//
//  Created by wes on 10/6/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface RKLeRadioServiceWrapper : NSObject


-(id) initWithService:(CBService*) service;

/* write new Tx Power to robot */
-(void) writeRemoteTxPower:(NSNumber*)txPower;
-(void) deepSleep;

@property (strong, nonatomic, readonly) CBService* service;

@property (strong, nonatomic, readonly) CBCharacteristic* wakeCharacteristic;
@property (strong, nonatomic, readonly) CBCharacteristic* txPowerCharacteristic;
@property (strong, nonatomic, readonly) CBCharacteristic* dosTimeoutInSecondsCharacteristic;

/*! hard stop main processor using radio */
@property (strong, nonatomic, readonly) CBCharacteristic* deepSleepCharacteristic;

@end
