//
//  RKMacroObject.h
//  RobotKit
//
//  Created by Jon Carroll on 9/11/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "RKSaveMacroCommand.h"
#import "RKMacroCommand.h"
#import "RKMCRoll.h"
#import "RKMCRGB.h"
#import "RKMCCalibrate.h"
#import "RKMCDelay.h"
#import "RKMCSlew.h"
#import "RKMCFrontLED.h"
#import "RKMCRotationRate.h"
#import "RKMCRotateOverTime.h"
#import "RKMCRawMotor.h"
#import "RKMCStabilization.h"
#import "RKMCSD1.h"
#import "RKMCSD2.h"
#import "RKMCSPD1.h"
#import "RKMCSPD2.h"
#import "RKMCRollSD1.h"
#import "RKMCRollSD1SPD1.h"
#import "RKMCRollSD1SPD2.h"
#import "RKMCRGBSD2.h"
#import "RKMCEmit.h"
#import "RKMCStreamEnd.h"
#import "RKMCWaitUntilStop.h"
#import "RKMCGoTo.h"
#import "RKMCSleep.h"
#import "RKMCLoopEnd.h"
#import "RKMCLoopFor.h"
#import "RKMCComment.h"
#import "RKMCGoSub.h"
#import "RKMCRotateOverTimeSD1.h"
#import "RKMCRotateOverTimeSD2.h"
#import "RKMCStop.h"

/*! @file */

/*!
 *  @brief   An object that represents a macro allowing modification.
 *
 *  A MacroObject represents a macro and allows adding and removing of commands
 *  that are subclasses of the RKMacroCommand.  The object can be initialized
 *  from a binary macro file and can generate binary data that represents the
 *  macro.
 *
 *  An RKMacroObject will also handle sending the macro to the robot in both
 *  a temporary mode and a cached streaming mode.
 */


/*!
 *  Type used to specify how macros are sent to the robot when play is called.
 */
typedef NS_ENUM(uint8_t, RKMacroObjectMode) {
   RKMacroObjectModeNormal = 0, /*! The default behavior, will send to ball as temporary macro when play is called, macro length limited to 254 bytes in this mode */
   RKMacroObjectModeCachedStreaming = 1, /*! Will cache commands and send them to the streaming macro (254) when play is called.  Allows for >254 byte macros */
   RKMacroObjectModeTemporaryChunk = 2 /*!Allows for macros up to 1024 bytes*/
};


@interface RKMacroObject : NSObject

// todo revisit privates
@property ( strong, nonatomic ) NSMutableArray *commands;
@property ( strong, nonatomic ) NSMutableArray *lastCommands;
@property ( strong, nonatomic ) NSMutableArray *chunkCommands;
@property ( strong, nonatomic, readonly ) NSMutableArray *ballMemory;


/*! The mode macros will be sent to the ball in when play is called */
@property RKMacroObjectMode mode;

/*! Yes if the macro is currently executing. */
@property (readwrite) BOOL running;

/*! Set to loop a macro in RKMacroObjectModeCachedStreaming */
@property BOOL loop;

/*! The macro flags that will be set if a macro is running in normal mode, default is RKMacroFlagsNone */
@property RKMacroFlags macroFlags;

/*! Initializer method
 *  @param data Binary macro data the macro should be initialized from. Use nil to create new macro.
 *  @return a new RKMacroObject initialized from data
 */
- (RKMacroObject*) initWithData:(NSData *) data;
+ (RKMacroObject*) objectWithData:(NSData*) data;

/*! Binary data representing the current macro
 *  @return NSData object containing binary data representing the macro
 */
- (NSData *) generateMacroData;

/*! Call to add a command to the macro
 *  @param command Command to be appended to the end of the macro
 */
- (void) addCommand:(RKMacroCommand *) command;

/*! Call to remove a command from the macro
 *  @param command Command to be removed from the macro
 */
- (void) removeCommand:(RKMacroCommand *) command;

/*! Call to move a command's position in the macro
 *  @param position1 Current index of the position to be moved
 *  @param position2 Index to move the command to.
 */
- (void) moveCommandAtPosition:(int) position1 toPosition:(int) position2;

/*! @deprecated - moved to RKMacroPlayer for multibot support */
//- (void) playMacro;

/*! @deprecated - moved to RKMacroPlayer for multibot support */
//- (void) stopMacro;

@end
