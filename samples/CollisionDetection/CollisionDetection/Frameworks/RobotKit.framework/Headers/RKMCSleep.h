//
//  RKMCSleep.h
//  RobotKit
//
//  Created by Jon Carroll on 11/18/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to put the robot to sleep
 *
 *  This command will put the robot to sleep
 */
@interface RKMCSleep : RKMacroCommand {
    int delay;
}

/*! The delay associated with the command. */
@property int delay;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param delay The delay associated with the command
 *  @return An instance of the command with the given parameters.
 */
+(RKMCSleep*)commandWithDelay:(int)delay;

@end
