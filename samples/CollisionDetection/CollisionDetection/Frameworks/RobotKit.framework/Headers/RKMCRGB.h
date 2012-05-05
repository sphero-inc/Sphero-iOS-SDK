//
//  MCRGB.h
//  MacroLab
//
//  Created by Jon Carroll on 9/11/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to control the RGB LED inside the robot
 *
 *  This command controls the output of the RGB LED inside of the robot
 *  Allowed values:
 *  red 0.0-1.0
 *  green 0.0-1.0
 *  blue 0.0-1.0
 *  delay 0-255
 */
@interface RKMCRGB : RKMacroCommand {
    float red;
    float green;
    float blue;
    int delay;
}

/*! The intensity of the red LED. 0.0-1.0 allowed. */
@property float red;

/*! The intensity of the green LED. 0.0-1.0 allowed. */
@property float green;

/*! The intensity of the blue LED. 0.0-1.0 allowed. */
@property float blue;

/*! The delay between this command and the previous command. 0-255 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param red The intensity of the red LED. 0.0-1.0 allowed.
 *  @param green The intensity of the green LED. 0.0-1.0 allowed.
 *  @param blue The intensity of the blue LED. 0.0-1.0 allowed.
 *  @param delay The delay between this command and the next command. 0-255 allowed.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCRGB*)commandWithRed:(float)red green:(float)green blue:(float)blue delay:(int)delay;

@end
