//
//  RKMCStreamEnd.h
//  RobotKit
//
//  Created by Jon Carroll on 11/4/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to indicate the end of a streaming macro (id 254)
 *
 *  Used in a streaming macro to indicate that a stream 
 */
@interface RKMCStreamEnd : RKMacroCommand

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCStreamEnd *) command;

@end
