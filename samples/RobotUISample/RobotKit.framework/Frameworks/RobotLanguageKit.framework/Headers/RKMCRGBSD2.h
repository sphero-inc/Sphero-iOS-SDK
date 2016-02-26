//
//  RKMCRGBSD2.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to control the RGB LED inside the robot using the System Delay 2 variable
 *
 *  This command controls the output of the RGB LED inside of the robot.
 *  A delay will be automatically added after the command that will be equal to the current
 *  value of the system delay 2 variable.  This can be set with the RKMCSD2 command.
 *  Allowed values:
 *  red 0.0-1.0
 *  green 0.0-1.0
 *  blue 0.0-1.0
 */
@interface RKMCRGBSD2 : RKMacroCommand {
   float red;
   float green;
   float blue;
}

/*! The intensity of the red LED. 0.0-1.0 allowed. */
@property float red;

/*! The intensity of the green LED. 0.0-1.0 allowed. */
@property float green;

/*! The intensity of the blue LED. 0.0-1.0 allowed. */
@property float blue;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param red The intensity of the red LED. 0.0-1.0 allowed.
 *  @param green The intensity of the green LED. 0.0-1.0 allowed.
 *  @param blue The intensity of the blue LED. 0.0-1.0 allowed.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCRGBSD2 *) commandWithRed:(float) red green:(float) green blue:(float) blue;

@end
