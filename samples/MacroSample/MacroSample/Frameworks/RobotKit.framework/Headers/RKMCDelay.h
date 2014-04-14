//
//  MCDelay.h
//  MacroLab
//
//  Created by Jon Carroll on 9/12/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "RKMacroCommand.h"


/*!
 *  @brief A command for adding a delay between commands
 *
 *  This command will allow you to add a delay between commands greater than the 255 ms
 *  delay limit on most commands.
 *  Allowed values:
 *  delay 0-65,535
 */
@interface RKMCDelay : RKMacroCommand {
   int delay;
}

/*! Delay in ms associated with this command. 0-65,535 allowed. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param delay The delay the command will be initialized with.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCDelay *) commandWithDelay:(int) delay;

@end
