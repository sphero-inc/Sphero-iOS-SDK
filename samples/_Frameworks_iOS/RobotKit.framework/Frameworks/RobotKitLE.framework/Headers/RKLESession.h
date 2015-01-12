//
//  RKLESession.h
//  RobotKitLE
//
//  Created by wes on 11/22/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RobotCommandKit.h>


@interface RKLESession : NSObject

+(id) sessionWithDelegate:(id<RKSessionDelegate>) delegate;

-(void) processRawData:(NSData*) rawBytesFromConnectedDevice;


-(NSData*) packetForCommand:(RKDeviceCommand*) command withACK:(BOOL) ack;
-(NSData*) packetForCommand:(RKDeviceCommand*) command;

@end
