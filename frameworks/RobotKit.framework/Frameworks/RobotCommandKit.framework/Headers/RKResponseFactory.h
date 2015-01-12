//
//  RKResponseFactory.h
//  RobotKit
//
//  Created by wes on 7/2/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKDeviceResponse.h"

@interface RKResponseFactory : NSObject

+ (RKDeviceResponse*) responseFromRawPacket:(NSData*) rawPacket withCommand:(RKDeviceCommand*) command;

+ (RKDeviceResponse*) timeoutResponseForCommand:(RKDeviceCommand*) command;

+ (RKResponseFactory*) singleton;

-(void) registerResponse:(Class) responseClass;

@end
