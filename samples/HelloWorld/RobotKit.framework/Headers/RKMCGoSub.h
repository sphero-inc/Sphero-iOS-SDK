//
//  RKMCGoSub.h
//  RobotKit
//
//  Created by Jon Carroll on 1/27/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Allows you to execute another macro inline inside of a macro
 *
 *  Allows execution of a macro inside of another macro.
 *  After the other macro execution has finished execution of the
 *  macro that issued the gosub command will continue.
 *  You can only GoSub 1 macro deep outside of the main main macro executing.
 *  GoSub commands inside a streaming macro (id 254) will be ignored.
 */
@interface RKMCGoSub : RKMacroCommand {
   uint8_t macroID;
}

/*! The identifier of the macro that should be executed inline. 0-253, 255 allowed */
@property uint8_t macroID;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param identifier The identifier of the macro that should be executed inline.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCGoSub *) commandWithID:(uint8_t) identifier;

@end
