//
//  MCStabilization.h
//  MacroLab
//
//  Created by Jon Carroll on 10/13/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"


/*!
 *  @brief Command to turn stabilization on/off
 *
 *  This command will turn stabilization on or off with a given delay after the command
 *  Allowed values:
 *  setting 0-1
 *  delay 0-255
 */
@interface RKMCStabilization : RKMacroCommand {
   int setting;
   int delay;
}

/*! The stabilization setting associated with the command 0=off 1=on. */
@property int setting;

/*! The delay after this command before the next command is executed. 0-255 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param setting The setting associated with the command
 *  @param delay The delay associated with this command
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCStabilization *) commandWithSetting:(int) setting delay:(int) delay;

@end
