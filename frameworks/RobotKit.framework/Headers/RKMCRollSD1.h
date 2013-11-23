//
//  RKMCRollSD1.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to roll the robot at a given heading and speed using system delay 1
 *
 *  This command will cause the robot to roll at the given heading and speed.
 *  The robot will continue rolling until a roll command with a speed of 0.0
 *  is issued. A delay will be automatically added after this command with the value
 *  specified in the system delay 1 variable.  This can be set using the MCSD1 command.
 *  Allowed values:
 *  speed 0.0-1.0
 *  heading 0-359
 */
@interface RKMCRollSD1 : RKMacroCommand {
    float speed;
    int heading;
}

/*! The speed at which the robot will roll. 0.0-1.0 allowed. */
@property float speed;

/*! The direction the robot will roll in. 0-359 allowed. */
@property int heading;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param speed The speed at which the robot will roll. 0.0-1.0 allowed.
 *  @param heading The direction the robot will roll in. 0-359 allowed.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCRollSD1*)commandWithSpeed:(float)speed heading:(int)heading;

@end
