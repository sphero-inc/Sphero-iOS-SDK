//
//  RKByNameConnectStrategy.h
//  RobotKitLE
//
//  Created by wes on 8/26/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKLeConnectStrategy.h"


@interface RKByNameConnectStrategy : NSObject <RKLeConnectStrategy>

@property (strong, nonatomic) NSString* deviceName;

-(id) initWithName:(NSString*) name;


@end
