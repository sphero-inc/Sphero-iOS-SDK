//
//  RKDeviceCommand.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceMessage.h>

/*!
 * @brief Base class for commands that can be sent to a robot.
 *
 * This is an abstract class that function as the base class for subclasses which encapsulates
 * the command set of a robot. The command objects can be sent to the robot by posting it to 
 * the RKDeviceMessenger singleton or by using on of the sendCommand class methods.
 * 
 * @sa RKDeviceMessage
 */
@interface RKDeviceCommand : RKDeviceMessage {
   NSTimeInterval transmitTimeStamp;
}

@property ( nonatomic, readonly ) NSTimeInterval transmitTimeStamp;


/*!
 * Convenience method that will send a simple command without parameter using the RKDeviceMessenger
 * singleton.
 */
+ (void) sendCommand;
/*!
 * Convenience method that will send a simple command without parameter using the RKDeviceMessenger
 * singleton.
 * @param delay A delay time in seconds to send the command.
 */
+ (void) sendCommandWithDelay:(NSTimeInterval) delay;
/*!
 * Method to send a command using a dictionary with a serialized command.
 * @sa sendCommandFromDict:
 * @param dict The serialized command in dictionary form.
 */
//+ (void) sendCommandFromDict:(NSDictionary *) dict;
/*!
 * Used to serialize the command into a dictionary.
 */
- (NSDictionary *) dictForCommand;
/*!
 * Convenience method that sends the command to the connected robot.
 */
- (void) sendCommand;
/*!
 * Convenience method that send the command after a delay to the connected robot.
 */
- (void) sendCommandWithDelay:(NSTimeInterval) delay;

@end
