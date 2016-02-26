//
//  RKDeviceInfoServiceWrapper.h
//  RobotKitLE
//
//  Created by wes on 5/13/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <RobotCommandKit/RobotCommandKit.h>

#import "RKRadioDescriptor.h"

@interface RKDeviceInfoServiceWrapper : NSObject

@property (weak, nonatomic, readonly) CBService* service;
@property (strong, nonatomic, readonly) RKMajorMinorVersion* rfVersion;
@property (strong, nonatomic, readonly) NSString* serialNumber;
@property (strong, nonatomic, readonly) NSString* manufacturerName;
@property (strong, nonatomic, readonly) NSString* modelNumber;
@property (strong, nonatomic, readonly) NSString* hardwareRevision;


-(id) initWithService:(CBService*) service andRadioDescriptor:(RKRadioDescriptor*) meta;

-(void) peripheral:(CBPeripheral *)peripheral didWriteValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

- (void)peripheral:(CBPeripheral *)peripheral didUpdateValueForCharacteristic:(CBCharacteristic *)characteristic error:(NSError *)error;

@end
