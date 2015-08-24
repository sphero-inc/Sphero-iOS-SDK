//
//  RKLeRadioMeta.h
//  RobotKitLE
//
//  Created by wes on 4/13/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "RKRadioDescriptor.h"

@interface RKRobotRadioDescriptor : RKRadioDescriptor

// ROBOT
@property (strong) CBUUID* uuidRobotService;
@property (strong) CBUUID* uuidControlCharacteristic;
@property (strong) CBUUID* uuidResponseCharacteristic;

+(id) ollieDescriptor;
+(id) bb8Descriptor;
+(id) weBallDescriptor;

-(id) initPrototypeDescriptor;

@end
