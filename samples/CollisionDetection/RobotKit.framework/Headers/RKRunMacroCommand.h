//
//  RKRunMacroCommand.h
//  RobotKit
//
//  Created by Brian Smith on 8/9/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RKDeviceCommand.h>

/*! Type for a macro identifier */
typedef uint8_t RKMacroIdType;

enum {
   /*! The identifier for the device's macro to move it in a figure eight pattern. */
         RKDeviceMacroIdFigureEight = 1,
   /*! The identifier for the device's macro to move it in a square pattern. */
         RKDeviceMacroIdSquare = 2
};


/*!
 * @brief Class that encapsulates a run macro command.
 *
 * This class is used to run a preloaded macro on Sphero. Macro are sets of commands that 
 * the device runs through instead of sending the individual commands.
 *
 * @sa RKRunMacroResponse
 */
@interface RKRunMacroCommand : RKDeviceCommand {
@private
   RKMacroIdType macroId;
}

/*! An identifier for the macro. */
@property ( nonatomic, readonly ) RKMacroIdType macroId;

/*!
 * Convenience class to send a run macro command with an identifier.
 * @param identifier The macro's identifier.
 */
+ (void) sendCommandWithId:(RKMacroIdType) identifier;
/*!
 *  The initializer for instances which sets the macro identefier.
 *
 * @param identifier The macro's identifier.
 * @return The initialized object.
 */
- (id) initWithId:(RKMacroIdType) identifier;

@end
