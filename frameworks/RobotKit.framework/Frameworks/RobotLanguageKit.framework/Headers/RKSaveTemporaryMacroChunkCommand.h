//
//  RKSaveTemporaryMacroChunkCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 3/2/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKSaveTemporaryMacroCommand.h"

/*!
 *  @brief Similar to RKSaveTemporaryMacroCommand but allow for saving long macros
 *
 *  Normally saving a macro has a length limit of 248 bytes, this command allows saving macros
 *  up to 1000 bytes in length.  The macro will need to be broken up into chunks of complete
 *  commands up to 250 bytes in length.  RKInitMacroExecutiveCommand will need to be sent before
 *  running a long macro.  Send the first chunk with the firstChunk flag set to YES/TRUE.  Chunks
 *  that follow should have the firstChunk flag set to NO/FALSE.  After saving chunks you can call
 *  the RKRunMacroCommand normally.
 *
 *  @sa RKInitMacroExecutiveCommand
 */

@interface RKSaveTemporaryMacroChunkCommand : RKSaveTemporaryMacroCommand {
@private
   BOOL firstChunk;
}

/*! Set if it is the first chunk to control sending of id byte and flags, default YES */
@property (readwrite) BOOL firstChunk;

+ (instancetype) commandWithMacro:(NSData *) data flags:(RKMacroFlags) flags;

@end
