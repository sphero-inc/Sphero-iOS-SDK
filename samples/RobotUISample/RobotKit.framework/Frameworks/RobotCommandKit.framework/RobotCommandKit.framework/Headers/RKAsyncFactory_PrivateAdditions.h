//
//  RKAsyncFactory_PrivateAdditions.h
//  RobotKit
//
//  Created by wes on 7/12/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RKAsyncFactory.h>

@interface RKAsyncFactory (PrivateAdditions)

-(void) registerClass:(Class) asyncClass;

@end
