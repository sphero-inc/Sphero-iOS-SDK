//
//  RKMCRotateOverTimeSD1.h
//  RobotKit
//
//  Created by Jon Carroll on 2/17/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief This command rotates the robot over the duration current set in SD1
 *
 *  This command will cause the robot to rotate inside the shell over the delay specified in SD1 @see RKMCSD1
 *  The robot can rotate at about 360 degrees per second.
 *  Allowed values:
 *  rotation -32,767-32,767
 */
@interface RKMCRotateOverTimeSD1 : RKMacroCommand {
   short rotation;
}

/*! The number of degrees the ball should rotate. -32,767-32,767 allowed */
@property short rotation;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param rotation The number of degrees the robot should rotate
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCRotateOverTimeSD1 *) commandWithRotation:(short) rotation;

@end
