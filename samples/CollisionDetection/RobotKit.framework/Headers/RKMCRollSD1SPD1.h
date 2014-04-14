//
//  RKMCRollSD1SPD1.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to roll the robot at a given heading using system speed 1 and system delay 1
 *
 *  This command will cause the robot to roll at the given heading. The system speed 1
 *  variable will be used with this command.  It can be set using the RKMCSPD1 command.
 *  The robot will continue rolling until a roll command with a speed of 0.0
 *  is issued. A delay will be automatically added after this command with the value
 *  specified in the system delay 1 variable.  This can be set using the MCSD1 command.
 *  Allowed values:
 *  heading 0-359
 */
@interface RKMCRollSD1SPD1 : RKMacroCommand {
   int heading;
}

/*! The direction the robot will roll in. 0-359 allowed. */
@property int heading;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param heading The direction the robot will roll in. 0-359 allowed.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCRollSD1SPD1 *) commandWithHeading:(int) heading;

@end
