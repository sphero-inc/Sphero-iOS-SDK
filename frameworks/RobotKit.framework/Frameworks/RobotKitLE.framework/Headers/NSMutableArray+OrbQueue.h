//
//  NSMutableArray+OrbQueue.h
//  RobotKitLE
//
//  Created by wes on 12/23/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSMutableArray (OrbQueue)


- (void) enqueue: (id)item;
- (id) dequeue;
- (id) peek;

@end
