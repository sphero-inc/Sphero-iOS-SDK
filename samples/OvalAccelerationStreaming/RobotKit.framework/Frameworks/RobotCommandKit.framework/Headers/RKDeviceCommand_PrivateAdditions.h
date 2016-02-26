//
//  RKDeviceCommand_PrivateAdditions.h
//  RobotCommandKit
//
//  Created by Brian Smith on 5/27/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @ignore */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKByteCommand.h"

@interface RKDeviceCommand (PrivateAdditions)

@property ( nonatomic, readonly ) uint8_t identifier;
@property ( nonatomic, readonly ) uint8_t deviceIdentifier;
@property ( nonatomic, readonly ) NSData *packedData;
@property ( nonatomic, readonly ) NSString *designator;
@property ( nonatomic, getter = isAsync, setter = setAsync: ) BOOL async;
@property (nonatomic, assign, readwrite) uint8_t sequenceNumber;

- (NSData *) packetize;
- (uint8_t) calculatePacketDataLength;

- (void) setTransmitTimeStamp:(NSTimeInterval) timeStamp;

// not all commands support this command.  Only Roll & RGB - intention is update DeviceCommand
// to always store packets like Unity Plugin.
- (id) initWithByteCommand:(RKByteCommand*) bCommand;


@end
