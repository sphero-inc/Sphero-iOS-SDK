//
//  MCRotateOverTime.h
//  MacroLab
//
//  Created by Jon Carroll on 9/21/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief This command rotates the robot over a given time.
 *
 *  This command will cause the robot to rotate inside the shell over the specified delay.
 *  The robot can rotate at about 360 degrees per second.
 *  Allowed values:
 *  delay 0-65,535
 *  rotation -32,767-32,767
 */
@interface RKMCRotateOverTime : RKMacroCommand {
    int delay;
    short rotation;
}

/*! The amount of time the rotation is allowed to complete. 0-65,535 allowed. */
@property int delay;

/*! The number of degrees the ball should rotate. -32,767-32,767 allowed */
@property short rotation;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param rotation The number of degrees the robot should rotate
 *  @param delay The delay the command will be initialized with.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCRotateOverTime*)commandWithRotation:(short)rotation delay:(int)delay;

@end
