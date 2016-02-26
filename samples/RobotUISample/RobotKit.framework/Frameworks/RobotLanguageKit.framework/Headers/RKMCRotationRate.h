//
//  MCRotationRate.h
//  MacroLab
//
//  Created by Jon Carroll on 9/12/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"


/*!
 *  @brief Sets the rotation rate of the ball
 *
 *  The command will immmedately set the rotation rate of the ball without a delay.
 *  Allowed values:
 *  rate 0.0-1.0
 */
@interface RKMCRotationRate : RKMacroCommand {
   float rate;
}

/*! The rotation rate to be set. 0.0-1.0 allowed. */
@property float rate;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param rate The rotation rate to set. 0.0-1.0 allowed.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCRotationRate *) commandWithRate:(float) rate;

@end
