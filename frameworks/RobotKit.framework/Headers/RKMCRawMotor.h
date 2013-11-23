//
//  MCRawMotor.h
//  MacroLab
//
//  Created by Jon Carroll on 10/13/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief A raw motor command to manually control the motors
 *
 *  A command to manually control the motors in the robot
 */
@interface RKMCRawMotor : RKMacroCommand {
    int leftMode;
    int leftSpeed;
    int rightMode;
    int rightSpeed;
    int delay;
}

/*! The mode the left motor is in */
@property int leftMode;

/*! The speed of the left motor */
@property int leftSpeed;

/*! The mode of the right motor */
@property int rightMode;

/*! The speed of the right motor */
@property int rightSpeed;

/*! The delay after this command before the next command, 0-255 allowed */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param leftMode The mode of the left motor
 *  @param leftSpeed The speed of the left motor
 *  @param rightMode The mode of the right motor
 *  @param rightSpeed The speed of the right motor
 *  @param delay The delay after this command before the next one
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCRawMotor *)commandWithLeftMode:(int)leftMode leftSpeed:(int)leftSpeed 
                            rightMode:(int)rightMode rightSpeed:(int)rightSpeed delay:(int)delay;


@end
