//
//  MCStop.h
//  MacroLab
//
//  Created by Adam Wilson on 5/6/13.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to send a Stop command to Sphero without altering heading
 *
 *  
 *  Allowed values:
 *  speed 0.0-1.0
 *  delay 0-255
 */
@interface RKMCStop : RKMacroCommand {
    float speed;
    int delay;
}

/*! The Speed to set the robot to, 0 by default:  0.0-1.0 allowed. */
@property float speed;

/*! The delay between this command and the next command in ms. 0-255 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param speed The Speed to set the robot to, 0 by default:  0.0-1.0 allowed.
 *  @param delay The delay between this command and the next command.  0-255 allowed.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCStop*)commandWithSpeed:(float)speed delay:(int)delay;

@end
