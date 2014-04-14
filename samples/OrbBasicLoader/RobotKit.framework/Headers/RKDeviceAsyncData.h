//
//  RKDeviceAsyncData.h
//  RobotKit
//
//  Created by Brian Smith on 7/7/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceMessage.h>

/*!
 * Base class for asynchronous messages that are sent with command. Most asynchronous 
 * messages have a command that has to be sent to enable them. There are a few message that are not
 * commanded like a sleep notification message. Client code can register as observers for asynchronous
 * using [RKDeviceMessenger addDataStreamingObserver: selector:].
 * @sa RKDeviceMessenger
 */
@interface RKDeviceAsyncData : RKDeviceMessage {
}

@property ( nonatomic, readonly ) NSInteger code;

@property ( readwrite ) int dataLength;

- (NSData*) data;

@end
