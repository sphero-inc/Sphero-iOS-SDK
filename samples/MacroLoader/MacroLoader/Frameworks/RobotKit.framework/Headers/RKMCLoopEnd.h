//
//  RKMCLoopEnd.h
//  RobotKit
//
//  Created by Jon Carroll on 1/27/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to mark the end of a loop
 *
 *  Placed after a RKMCLoopFor command to mark the end of a loop
 */
@interface RKMCLoopEnd : RKMacroCommand

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @return An instance of the command with the given parameters.
 */
+(RKMCLoopEnd*)command;

@end
