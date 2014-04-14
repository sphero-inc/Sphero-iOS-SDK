//
//  RKMCGoTo.h
//  RobotKit
//
//  Created by Jon Carroll on 11/10/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to cause the macro exec to goto another macro
 *
 *  This command can be used to chain macros togother or to loop macros.
 *  This can be used in RKMacroObjectModeNormal to loop by using macroID 255.
 *  This command cannot be used in RKMacroObjectModeCachedStreaming.
 *  This command will not allow you to goto the streaming macro (id 254).
 *  Allowed values:
 *  macroID 0-253, 255
 */
@interface RKMCGoTo : RKMacroCommand {
   uint8_t macroID;
}

/*! The identifier of the macro execution should continue at the beginning of. 0-253, 255 allowed */
@property uint8_t macroID;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param identifier The identifier of the macro that execution should continue at the beginning of.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCGoTo *) commandWithID:(uint8_t) identifier;

@end
