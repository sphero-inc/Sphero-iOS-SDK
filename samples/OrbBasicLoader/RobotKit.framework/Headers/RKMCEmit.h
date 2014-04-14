//
//  RKMCEmit.h
//  RobotKit
//
//  Created by Jon Carroll on 10/30/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Command to cause an asyncronous emit from the ball
 *
 *  Command that will cause the ball to generate an asyncronous emit command
 *  when the command is encountered with the specified emit identifier.
 *  Allowed values:
 *  identifier 0-255
 *
 *  Emit identifiers 0-10 are reserved for internal SDK use, avoid using them
 */
@interface RKMCEmit : RKMacroCommand {
   uint8_t emitID;
}

/*! The identifier that will be associated with the generated emit */
@property uint8_t emitID;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param identifier The identifier that will be associated with the emit that is generated.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCEmit *) commandWithID:(uint8_t) identifier;

@end
