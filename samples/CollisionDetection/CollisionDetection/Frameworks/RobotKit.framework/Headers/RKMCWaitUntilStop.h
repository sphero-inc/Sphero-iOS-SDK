//
//  RKMCWaitUntilStop.h
//  RobotKit
//
//  Created by Jon Carroll on 11/10/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to cause the robot to wait until it has come to a complete stop
 *
 *  Use this command after a roll command with a speed of 0.0.  Macro execution
 *  will not continue until the robot has come to a complete stop or the time
 *  specified by delay has expired.
 *  Allowed values:
 *  delay 0-65,353
 */
@interface RKMCWaitUntilStop : RKMacroCommand {
    int delay;
}

/*! The amount of time to wait for the robot to come to a complete stop */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param delay The delay associated with the command. 0-65,353 allowed.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCWaitUntilStop*)commandWithDelay:(int)delay;

@end
