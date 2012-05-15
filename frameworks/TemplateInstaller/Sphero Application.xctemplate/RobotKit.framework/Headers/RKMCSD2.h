//
//  RKMCSD2.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Sets the system delay 2 variable used by RGB commands
 *
 *  This command sets the system delay 1 variable that is used by RGB
 *  commands that don't have a specified delay.
 *  Allowed values:
 *  delay 0-65,535
 */
@interface RKMCSD2 : RKMacroCommand {
    int delay;
}

/*! The delay associated with the command. 0-63,353 allowed */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param delay The delay the command will be initialized with.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCSD2*)commandWithDelay:(int)delay;

@end
