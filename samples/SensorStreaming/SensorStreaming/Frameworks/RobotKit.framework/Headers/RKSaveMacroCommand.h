//
//  RKSaveMacroCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#if defined (SRCLIBRARY)
#import <RobotKit/Macro/RKSaveTemporaryMacroCommand.h>
#else
#import <RobotKit/RKSaveTemporaryMacroCommand.h>
#endif

/*!
 * @brief Class to encapsulate a save macro command.
 *
 * This class is used to send a macro to save on Sphero. A special macro identifier of 254
 * is used to stream macro which allows client code to send multiple blocks which get appended
 * on the device. Use the abort command or a special END code end the streaming.
 * 
 * NOTE: THE FIRMWARE AS OF 1.13 ONLY SUPPORTS MACRO STREAMING AND IT WILL NOT SAVE A MACRO 
 * WITH AN IDENTIFIER LESS THAN 254. USE RKSaveTemporaryMacroCommand TO SAVE A MACRO TO IDENTIFIER 
 * 255 AND USE THIS CLASS TO STREAM.
 *
 * @sa RKSaveTemporaryMacroCommand
 *
 */
@interface RKSaveMacroCommand : RKDeviceCommand {
    @private
    RKMacroFlags  macroFlags;
    NSData        *macro;
    uint8_t       macroID;
}

/*! Flags that are used with the macro. @sa RKSaveTemporaryMacroCommand for the flags. */
@property (nonatomic, readonly) RKMacroFlags    macroFlags;
/*! A NSData object which contains the macro. */
@property (nonatomic, readonly) NSData          *macro;
/*! An idenitifier for the macro. */
@property (nonatomic, readonly) uint8_t         macroID;

/*!
 * Convenience command to send the save macro command.
 * @param data The macro contained in an NSData object. 
 * @param identifier The macro identifier. Identifier 254 is reserved for streaming macro and 255
 * is for a temporary macro. 
 * @param flags A bitwise OR set of macro flags. 
 */
+ (void)sendCommandWithMacro:(NSData *)data macroID:(uint8_t)identifier flags:(RKMacroFlags)flags;
/*!
 * Convenience command to send the save macro command with a delay.
 * @param data The macro contained in an NSData object. 
 * @param identifier The macro identifier. Identifier 254 is reserved for streaming macro and 255
 * is for a temporary macro. 
 * @param flags A bitwise OR set of macro flags. 
 * @param delay A delay in seconds befor sending the command to a device.
 */
+ (void)sendCommandWithMacro:(NSData *)data macroID:(uint8_t)identifier flags:(RKMacroFlags)flags delay:(NSTimeInterval)delay;

/*!
 * 
 * Intialize for RKSaveMacroCommand objects that sets the macro, flags, and identifier.
 *
 * @param data The macro as binary data.
 * @param identifier The macro identifier. Identifier 254 is reserved for streaming macro and 255
 * is for a temporary macro. 
 * @param flags A bitwise OR set of macro flags. 
 */
- (id)initWithMacro:(NSData *)data macroID:(uint8_t)identifier flags:(RKMacroFlags)flags;

@end
