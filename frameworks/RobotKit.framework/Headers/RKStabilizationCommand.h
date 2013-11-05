//
//  RKStabilizationCommand.h
//  RobotKit
//
//  Created by Brian Smith on 9/9/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! Enumerations for stabilization states. */
enum RKStabilizationState {
   RKStabilizationStateOff = 0, /*!< Turns off stabilization */
      RKStabilizationStateOn = 1,  /*!< Turns on stabilization with the control system reset. */
   /*! Turns on stabilization but keeps the control system in the state it was before turning off
    *  stabilization. Available main app version 0.95 or greater
    */
         RKStabilizationStateOnNoReset = 2
};
/*! Defines a type for stabilization state. */
typedef enum RKStabilizationState RKStabilizationState;


/*! @brief Class that encapsulates a stabilization command.
 *
 * This class is used to turn of the control system on Sphero which stabilizes it.
 *
 * @sa RKStabilizationResponse
 */
@interface RKStabilizationCommand : RKDeviceCommand {
@private
   RKStabilizationState state;
}

/*! The new state to set. */
@property ( nonatomic, readonly ) RKStabilizationState state;

/*! 
 * Convenience method for sending the stabilization command. 
 *
 * @param state The new state for the control system stabilization.
 */
+ (void) sendCommandWithState:(RKStabilizationState) state;
/*! 
 * 
 * The initializer for the object which is used set the state of stabilization.
 *
 * @param state The new state for the control system stabilization.
 * @return The initialized object.
 */
- (id) initWithState:(RKStabilizationState) state;

@end
