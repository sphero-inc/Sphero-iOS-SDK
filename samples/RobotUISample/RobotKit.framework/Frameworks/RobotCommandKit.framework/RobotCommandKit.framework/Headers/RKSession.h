//
//  RKLESession.h
//  RobotKitLE
//
//  Created by wes on 11/22/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKDeviceAsyncData.h"
#import "RKDeviceCommand.h"

@protocol RKSessionDelegate <NSObject>

-(void) handleResponse:(RKDeviceResponse*) response;

-(void) handleStringResponse:(NSString*) stringResponse;

-(void) handleAsyncData:(RKAsyncMessage*) asyncData;

@end

@interface RKSession : NSObject

+(id) sessionWithDelegate:(id<RKSessionDelegate>) delegate;

+ (void)setMaxNativeSequenceNumber:(uint8_t)sequenceNumber;
-(void) processRawData:(NSData*) rawBytesFromConnectedDevice;


-(NSData*) packetForCommand:(RKDeviceCommand*) command withACK:(BOOL) ack;
-(NSData*) packetForCommand:(RKDeviceCommand*) command;

@end
