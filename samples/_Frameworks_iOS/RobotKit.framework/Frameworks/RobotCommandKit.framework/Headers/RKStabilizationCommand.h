//
//  RKStabilizationCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 9/9/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! Enumerations for stabilization states. */
typedef NS_ENUM(uint8_t, RKStabilizationState) {
	/*!< Turns off stabilization */
	RKStabilizationStateOff = 0,
	/*!< Turns on stabilization with the control system reset. */
	RKStabilizationStateOn = 1,
	/*! Turns on stabilization but keeps the control system in the state it was before turning off
	 *  stabilization. Available main app version 0.95 or greater
	 */
	RKStabilizationStateOnNoReset = 2
};


/*! @brief Class that encapsulates a stabilization command.
 *
 * This class is used to turn of the control system on Sphero which stabilizes it.
 *
 * @sa RKStabilizationResponse
 */
@interface RKStabilizationCommand : RKDeviceCommand

/*! The new state to set. */
@property ( nonatomic, readonly ) RKStabilizationState state;

/*!
 *
 * The initializer for the object which is used set the state of stabilization.
 *
 * @param state The new state for the control system stabilization.
 * @return The initialized object.
 */
- (instancetype) initWithState:(RKStabilizationState) state;

+ (instancetype) commandWithState:(RKStabilizationState) state;

@end
