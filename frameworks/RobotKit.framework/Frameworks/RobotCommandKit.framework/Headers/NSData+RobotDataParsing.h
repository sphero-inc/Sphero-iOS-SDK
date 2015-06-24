//
//  NSData+RobotDataParsing.h
//  RobotCommandKit
//
//  Created by wes on 6/30/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (RobotDataParsing)

-(uint32_t) uint32Value;
-(uint16_t) uint16Value;
-(float) fixedPoint16Value;
- (NSData *)reverse;

@end
