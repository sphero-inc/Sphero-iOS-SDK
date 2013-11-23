//
//  RKMCLoopFor.h
//  RobotKit
//
//  Created by Jon Carroll on 1/27/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief A command to mark the beginning of a loop
 *
 *  Place command at the beginning of a set of commands to loop.
 *  Place a RKMCLoopEnd command at the end of the commands to loop.
 */
@interface RKMCLoopFor : RKMacroCommand {
    uint8_t repeats;
}

/*! Number of times to loop */
@property uint8_t repeats;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param repeats The number of times the loop will repeat
 *  @return An instance of the command with the given parameters.
 */
+(RKMCLoopFor*)commandWithRepeats:(uint8_t)repeats;

@end
