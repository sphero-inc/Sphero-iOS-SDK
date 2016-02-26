//
//  RKLeBaseLink.h
//  RobotKitLE
//
//  Created by Corey Earwood on 10/9/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"
#import <CoreBluetooth/CoreBluetooth.h>

@interface RKLeBaseLink : NSObject <CBPeripheralDelegate, RKLeNode>

@end
