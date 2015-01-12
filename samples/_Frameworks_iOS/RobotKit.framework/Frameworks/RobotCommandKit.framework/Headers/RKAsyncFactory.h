//
//  RKAsyncFactory.h
//  RobotKit
//
//  Created by wes on 7/9/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKDeviceAsyncData.h"

@interface RKAsyncFactory : NSObject

+ (RKAsyncMessage*) dataFromPacket:(NSData*) asyncPacket;

+ (RKAsyncFactory*) singleton;

+ (RKAsyncFactory*) factory;

-(void) registerClass:(Class) asyncClass;

@end
