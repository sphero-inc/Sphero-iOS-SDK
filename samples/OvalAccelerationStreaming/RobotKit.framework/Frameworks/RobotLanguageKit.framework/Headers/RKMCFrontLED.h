//
//  MCFrontLED.h
//  MacroLab
//
//  Created by Jon Carroll on 9/12/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to control the Back LED on the robot
 *
 *  Used to control the intensity of the Back LED on the robot
 *  Allowed values:
 *  intensity 0.0-1.0
 *  delay 0-255
 */
@interface RKMCFrontLED : RKMacroCommand {
   float intensity;
   int delay;
}

/*! The intensity the back LED will be lit at. 0.0-1.0 allowed. */
@property float intensity;

/*! The delay between this command and the next command in ms. 0-255 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param intensity The intensity the Back LED will be lit at. 0.0-1.0 allowed.
 *  @param delay The delay between this command and the next command.  0-255 allowed.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCFrontLED *) commandWithIntensity:(float) intensity delay:(int) delay;

@end
