//
//  RKOrbBasicAppendFragmentCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 3/16/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceCommand.h>
#import <RobotKit/RKTypes.h>

/*!
 *  Command to append complete lines of orb basic code to ball memory.
 *  Fragment data should be ascii encoded string.
 *  Sending an orbBasic program to Sphero involves appending complete lines 
 *  to any existing ones in the specified storage area. Complete lines are 
 *  required. A line begins with a decimal line number followed by a space 
 *  and is terminated with a <CR>.
 */
@interface RKOrbBasicAppendFragmentCommand : RKDeviceCommand {
@private
   RKOrbBasicStorageType storageType;
   NSData *fragment;
}

/* Convenience method to send a code fragment to the ball */
+ (void) sendCommandWithStorageType:(RKOrbBasicStorageType) storageType fragment:(NSData *) fragment;

/* Initialize a command fragment with code */
- (id) initWithStorageType:(RKOrbBasicStorageType) type fragment:(NSData *) frag;

@end
