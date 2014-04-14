//
//  RKRemoteRobot.h
//  RobotKit
//
//  Created by Jon Carroll on 8/9/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RKDeviceCommand;
@class RKRemotePlayer;


/*!
 *  @brief RKRemoteRobot represents a remote player's robot and allows for remote control
 *
 *  Commands can be sent by creating instances of the RKDeviceCommand subclass you want to
 *  send and calling the sendCommand method on the remote player's RKRemoteRobot instance.
 *  Currently only commands with meaningless responses are supported (e.g. no data streaming
 *  or ping commands).  There will be no response for the commands.  They are gurunteed to be
 *  delivered to the remote device but there is no guaruntee the robot will recieve them.
 *  A general rule to ensure the robot recieves the commands is to only send one command
 *  every 0.2 seconds.
 *
 *  See Also:
 *  @sa RKRemotePlayer
 *  @sa RKMultiplayer
 *  @sa RKMultiplayerGame
 */
@interface RKRemoteRobot : NSObject

/*! Represents the remote player associated with this robot. */
@property ( nonatomic, strong ) RKRemotePlayer *player;

/*! Used to send commands to a remote robot
 */
- (void) sendCommand:(RKDeviceCommand *) command;

/*! Used internally by RKMultiplayer to process remote commands to local robot 
 */
+ (void) processCommand:(NSDictionary *) dict;

@end
