//
//  MCSlew.h
//  MacroLab
//
//  Created by Jon Carroll on 9/12/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to fade the RGB LED in the robot to the specified color
 *
 *  This command controls the output of the RGB LED inside of the robot by
 *  fading from the current color to the specified color. You will usually
 *  want to follow this command with a RKMCDelay command of equal length.
 *  Allowed values:
 *  red 0.0-1.0
 *  green 0.0-1.0
 *  blue 0.0-1.0
 *  delay 0-65,353
 */
@interface RKMCSlew : RKMacroCommand {
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

/*! The duration of the fade in ms. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param red The intensity of the red LED. 0.0-1.0 allowed.
 *  @param green The intensity of the green LED. 0.0-1.0 allowed.
 *  @param blue The intensity of the blue LED. 0.0-1.0 allowed.
 *  @param delay The duration of the fade
 *  @return An instance of the command with the given parameters.
 */
+(RKMCSlew*)commandWithRed:(float)red green:(float)green blue:(float)blue delay:(int)delay;

@end
