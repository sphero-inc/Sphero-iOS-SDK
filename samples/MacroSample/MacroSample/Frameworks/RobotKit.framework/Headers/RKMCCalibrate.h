//
//  MCCalibrate.h
//  MacroLab
//
//  Created by Jon Carroll on 9/12/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Macro Command to calibrate the robot
 *
 *  When this command is sent the current heading of the robot will become
 *  the heading that is passed in as a parameter.
 *  Allowed values:
 *  heading 0-359
 *  delay 0-255
 */

@interface RKMCCalibrate : RKMacroCommand {
   int heading;
   int delay;
}

/*! The current heading of the robot will become this value after the command is executed. 0-359 allowed. */
@property int heading;

/*! The delay in ms after this command is executed before the next command is. 0-255 allowed.*/
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param heading The heading the command will be initialized with.
 *  @param delay The delay the command will be initialized with
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCCalibrate *) commandWithHeading:(int) heading delay:(int) delay;

@end
