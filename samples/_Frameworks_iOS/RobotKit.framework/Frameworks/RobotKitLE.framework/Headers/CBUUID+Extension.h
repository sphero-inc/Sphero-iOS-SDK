//
//  CBUUID+Extension.h
//  RobotKitLE
//
//  Created by wes on 3/29/14.
//  Copyright (c) 2014 Orbotix. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

@interface CBUUID (Extension)

//-(BOOL) isEqualToStringUUID:(NSString*) uuid;
-(NSString *)getStringRepresentation;

@end
