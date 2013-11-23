//
//  RKDeviceMessenger.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RKDeviceCommand;
@class RKRobot;
@class RKDeviceConnection;

/*!
 * @brief Singleton to provide a messaging framework for command and responses.
 *
 * Use to listen to command responses and streaming data.
 * 
 */
@interface RKDeviceMessenger : NSObject {
    @private
	RKDeviceConnection  *connection;
	NSMutableArray      *responseObservers;
    NSLock              *responseObserversLock;
    NSMutableArray      *dataStreamingObservers;
    NSLock              *dataStreamingOberversLock;
}

/*! Accessor to the singleton. */
+ (RKDeviceMessenger *)sharedMessenger;

/*! 
 * Method for posting a command in the command queue to be sent to a robot. 
 * @param command The command object to post to the command queue.
 */
- (void)postCommand:(RKDeviceCommand *)command;
/*!
 * Method for posting a command in the command queue to be sent to a robot with a delay. 
 * @param command The command to post to the command queue.
 * @param delay A delay in seconds before the command is queued.
 */
- (void)postCommand:(RKDeviceCommand *)command delay:(NSTimeInterval)delay;
/*! 
 * Adds an observer for response objects return for commands.
 * @param observer The observer for responses.
 * @param handler A selector that will be called on the observer with a signiture of 
 * -handleResponse:(RKDeviceResponse *)response.
 */
- (void)addResponseObserver:(id)observer selector:(SEL)handler;
/*! 
 * Removes an response observer.
 * @param observer The observer.
 */
- (void)removeResponseObserver:(id)observer;

/*!
 * Adds an observer for data streaming. Data streaming are packets of data
 * that is sent from the device without being commanded.
 * @param observer The observer. Only one selector per observer is allowed.
 * @param handler A selector of the form - (void)handDataStreaming:(RKDeviceAsyncData *)data
 */
- (void)addDataStreamingObserver:(id)observer selector:(SEL)handler;

/*!
 * Removes an observer from receiving asynchronize data
 @ @param observer The observer to remove.
 */
- (void)removeDataStreamingObserver:(id)observer;

@end
