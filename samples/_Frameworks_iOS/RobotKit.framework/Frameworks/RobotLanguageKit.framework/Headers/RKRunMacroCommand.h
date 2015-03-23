//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotCommandKit/RKDeviceCommand.h>

typedef NS_ENUM(uint8_t, RKMacroIdType) {
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
@interface RKRunMacroCommand : RKDeviceCommand

/*! An identifier for the macro. */
@property ( nonatomic, readonly ) RKMacroIdType macroId;

/*!
 *  The initializer for instances which sets the macro identefier.
 *
 * @param identifier The macro's identifier.
 * @return The initialized object.
 */
- (instancetype) initWithId:(RKMacroIdType) identifier;

+ (instancetype) commandWithId:(RKMacroIdType) identifier;


@end
