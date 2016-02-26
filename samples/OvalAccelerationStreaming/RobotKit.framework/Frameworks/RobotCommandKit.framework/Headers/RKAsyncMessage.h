//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import "RKDeviceMessage.h"

/*!
 * Base class for asynchronous messages that are sent with command. Most asynchronous
 * messages have a command that has to be sent to enable them. There are a few message that are not
 * commanded like a sleep notification message.
 */
@interface RKAsyncMessage : RKDeviceMessage

- (id) initWithAsyncPacket:(NSData*) packet;

@property ( nonatomic, readonly ) NSInteger code;

@property ( nonatomic, readonly ) NSInteger dataLength;

- (NSData*) data;

@end
