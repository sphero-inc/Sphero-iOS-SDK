//
//  RKMacroObject.h
//  RobotKit
//
//  Created by Jon Carroll on 9/11/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if defined (SRCLIBRARY)
#import <RobotKit/Macro/RKSaveMacroCommand.h>
#import <RobotKit/Macro/RKMacroCommand.h>
#import <RobotKit/Macro/RKMCRoll.h>
#import <RobotKit/Macro/RKMCRGB.h>
#import <RobotKit/Macro/RKMCCalibrate.h>
#import <RobotKit/Macro/RKMCDelay.h>
#import <RobotKit/Macro/RKMCSlew.h>
#import <RobotKit/Macro/RKMCFrontLED.h>
#import <RobotKit/Macro/RKMCRotationRate.h>
#import <RobotKit/Macro/RKMCRotateOverTime.h>
#import <RobotKit/Macro/RKMCRawMotor.h>
#import <RobotKit/Macro/RKMCStabilization.h>
#import <RobotKit/Macro/RKMCSD1.h>
#import <RobotKit/Macro/RKMCSD2.h>
#import <RobotKit/Macro/RKMCSPD1.h>
#import <RobotKit/Macro/RKMCSPD2.h>
#import <RobotKit/Macro/RKMCRollSD1.h>
#import <RobotKit/Macro/RKMCRollSD1SPD1.h>
#import <RobotKit/Macro/RKMCRollSD1SPD2.h>
#import <RobotKit/Macro/RKMCRGBSD2.h>
#import <RobotKit/Macro/RKMCEmit.h>
#import <RobotKit/Macro/RKMCStreamEnd.h>
#import <RobotKit/Macro/RKMCWaitUntilStop.h>
#import <RobotKit/Macro/RKMCGoTo.h>
#import <RobotKit/Macro/RKMCSleep.h>
#import <RobotKit/Macro/RKMCLoopEnd.h>
#import <RobotKit/Macro/RKMCLoopFor.h>
#import <RobotKit/Macro/RKMCComment.h>
#import <RobotKit/Macro/RKMCGoSub.h>
#import <RobotKit/Macro/RKMCRotateOverTimeSD1.h>
#import <RobotKit/Macro/RKMCRotateOverTimeSD2.h>
#import <RobotKit/Macro/RKMCStop.h>
#else

#import <RobotKit/RKSaveMacroCommand.h>
#import <RobotKit/RKMacroCommand.h>
#import <RobotKit/RKMCRoll.h>
#import <RobotKit/RKMCRGB.h>
#import <RobotKit/RKMCCalibrate.h>
#import <RobotKit/RKMCDelay.h>
#import <RobotKit/RKMCSlew.h>
#import <RobotKit/RKMCFrontLED.h>
#import <RobotKit/RKMCRotationRate.h>
#import <RobotKit/RKMCRotateOverTime.h>
#import <RobotKit/RKMCRawMotor.h>
#import <RobotKit/RKMCStabilization.h>
#import <RobotKit/RKMCSD1.h>
#import <RobotKit/RKMCSD2.h>
#import <RobotKit/RKMCSPD1.h>
#import <RobotKit/RKMCSPD2.h>
#import <RobotKit/RKMCRollSD1.h>
#import <RobotKit/RKMCRollSD1SPD1.h>
#import <RobotKit/RKMCRollSD1SPD2.h>
#import <RobotKit/RKMCRGBSD2.h>
#import <RobotKit/RKMCEmit.h>
#import <RobotKit/RKMCStreamEnd.h>
#import <RobotKit/RKMCWaitUntilStop.h>
#import <RobotKit/RKMCGoTo.h>
#import <RobotKit/RKMCSleep.h>
#import <RobotKit/RKMCLoopEnd.h>
#import <RobotKit/RKMCLoopFor.h>
#import <RobotKit/RKMCComment.h>
#import <RobotKit/RKMCGoSub.h>
#import <RobotKit/RKMCRotateOverTimeSD1.h>
#import <RobotKit/RKMCRotateOverTimeSD2.h>
#import <RobotKit/RKMCStop.h>

#endif

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
typedef enum {
   RKMacroObjectModeNormal = 0, /*! The default behavior, will send to ball as temporary macro when play is called, macro length limited to 254 bytes in this mode */
         RKMacroObjectModeCachedStreaming = 1, /*! Will cache commands and send them to the streaming macro (254) when play is called.  Allows for >254 byte macros */
         RKMacroObjectModeTemporaryChunk = 2 /*!Allows for macros up to 1024 bytes*/
} RKMacroObjectMode;


@interface RKMacroObject : NSObject {
@private
   NSMutableArray *commands;
   NSMutableArray *lastCommands;
   NSMutableArray *ballMemory;
   RKMacroObjectMode mode;
   BOOL running;
   BOOL registeredObserver;
   BOOL commandOutstanding;
   BOOL loop;
   RKMacroFlags macroFlags;
   NSMutableArray *chunkCommands;
}

/*! An array of RKMacroCommand objects that make up the macro */
@property ( nonatomic, readonly ) NSMutableArray *commands;

/*! The mode macros will be sent to the ball in when play is called */
@property RKMacroObjectMode mode;

/*! Yes if the macro is currently executing. */
@property BOOL running;

/*! Set to loop a macro in RKMacroObjectModeCachedStreaming */
@property BOOL loop;

/*! The macro flags that will be set if a macro is running in normal mode, default is RKMacroFlagsNone */
@property RKMacroFlags macroFlags;

/*! Initializer method
 *  @param data Binary macro data the macro should be initialized from. Use nil to create new macro.
 *  @return a new RKMacroObject initialized from data
 */
- (RKMacroObject *) initWithData:(NSData *) data;

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

/*! Sends the macro in it's current state to the ball using the current RKMacroObjectMode setting. */
- (void) playMacro;

/*! Stops executing the current macro. */
- (void) stopMacro;

@end
