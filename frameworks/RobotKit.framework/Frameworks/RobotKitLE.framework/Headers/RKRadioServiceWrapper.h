//
//  RKLeRadioServiceWrapper.h
//  RobotKitLE
//
//  Created by wes on 10/6/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "RKRobotRadioDescriptor.h"

typedef NS_ENUM (uint8_t, RKLEWakeType){
	RKLeWakeType_Normal = 0x01,
	RKLeWakeType_Silent = 0x02
};


@protocol RKRadioServiceWrapperDelegate

@end


@interface RKRadioServiceWrapper : NSObject

-(id) initWithService:(CBService*) service andRadioDescriptor:(RKRadioDescriptor*) meta;

/* write new Tx Power to robot */
-(void) writeRemoteTxPower:(NSNumber*)txPower;
-(void) requestMainProcessorPowerOn:(RKLEWakeType) type;
-(void) enableRemoteRSSIMonitor:(uint16_t) pingIntervalInSeconds; // min 1/4 second
-(void) readRemoteRSSI;
-(void) deepSleep;

- (void)peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;
- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

@property (strong, nonatomic, readonly) CBService* service;

@property (strong, nonatomic, readonly) CBCharacteristic* wakeCharacteristic;
@property (strong, nonatomic, readonly) CBCharacteristic* txPowerCharacteristic;
@property (strong, nonatomic, readonly) CBCharacteristic* dosTimeoutInSecondsCharacteristic;

/*! hard stop main processor using radio */
@property (strong, nonatomic, readonly) CBCharacteristic* deepSleepCharacteristic;

/*! introduced 'read' in radio 1.37
 Updated to 'write' 'notify' in radio 1.40 */
@property (strong, nonatomic, readonly) CBCharacteristic* rssiCharacteristic;

@end
