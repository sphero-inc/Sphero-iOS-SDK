//
//  MCRoll.h
//  MacroLab
//
//  Created by Jon Carroll on 9/11/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to roll the robot at a given heading and speed
 *
 *  This command will cause the robot to roll at the given heading and speed.
 *  The robot will continue rolling until a roll command with a speed of 0.0
 *  is issued.
 *  Allowed values:
 *  speed 0.0-1.0
 *  heading 0-359
 *  delay 0-255
 */
@interface RKMCRoll : RKMacroCommand {
    float speed;
    int heading;
    int delay;
}

/*! The speed at which the robot will roll. 0.0-1.0 allowed. */
@property float speed;

/*! The direction the robot will roll in. 0-359 allowed. */
@property int heading;

/*! The delay between this command and the next command. 0-255 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param speed The speed at which the robot will roll. 0.0-1.0 allowed.
 *  @param heading The direction the robot will roll in. 0-359 allowed.
 *  @param delay The delay between this command and the next command. 0-255 allowed.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCRoll*)commandWithSpeed:(float)speed heading:(int)heading delay:(int)delay;

@end
