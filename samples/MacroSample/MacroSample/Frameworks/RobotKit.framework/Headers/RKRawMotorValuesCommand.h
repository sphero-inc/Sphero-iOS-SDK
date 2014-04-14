//
//  RKRawMotorValuesCommand.h
//  RobotKit
//
//  Created by Brian Smith on 9/9/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! Enumerations for the possible raw motor modes. */
enum RKRawMotorMode {
   RKRawMotorModeOff = 0, /*!< Mode to set the motor off */
      RKRawMotorModeForward = 1, /*!< Mode to set the motor to turn forward. */
      RKRawMotorModeReverse = 2, /*!< Mode to set the motor to turn backward. */
      RKRawMotorModeBrake = 3, /*!< Mode to brake the motors. */
      RKRawMotorModeIgnore = 4  /*!< Mode to ignore the motor power value. */
};
/*! Defines a type for the raw motor modes. */
typedef enum RKRawMotorMode RKRawMotorMode;

/*! Type for the motor power. */
typedef uint8_t RKRawMotorPower;


/*!
 * @brief Class to encapsulate a raw motor values command.
 * 
 * This command is used to set raw motor values to move the ball without the control system
 * maintaining a heading and speed. The control system stabilization engine will be turned off
 * when this command is run, and clients need to use RKStabilizationCommand to turn it back
 * on. 
 *
 * @sa RKRawMotorValuesCommand
 */
@interface RKRawMotorValuesCommand : RKDeviceCommand {
@private
   RKRawMotorMode leftMotorMode;
   RKRawMotorPower leftMotorPower;
   RKRawMotorMode rightMotorMode;
   RKRawMotorPower rightMotorPower;
}

/*! Read only property for left motor mode. */
@property ( nonatomic, readonly ) RKRawMotorMode leftMotorMode;
/*! Read only property for the left motor power. This is a value from 0 to 255. */
@property ( nonatomic, readonly ) RKRawMotorPower leftMotorPower;
/*! Read only property for right motor mode. */
@property ( nonatomic, readonly ) RKRawMotorMode rightMotorMode;
/*! Read only property for the right motor power. This is a value from 0 to 255. */
@property ( nonatomic, readonly ) RKRawMotorPower rightMotorPower;

/*!
 * Convenience method to send a raw motor values command.
 * @param leftMode The left motor mode.
 * @param leftPower A value from 0 to 255 for the power to applied to the motor.
 * @param rightMode The right motor mode.
 * @param rightPower A value from 0 to 255 for the power to applied to the motor.
 */
+ (void) sendCommandWithLeftMode:(RKRawMotorMode) leftMode leftPower:(RKRawMotorPower) leftPower
                       rightMode:(RKRawMotorMode) rightMode rightPower:(RKRawMotorPower) rightPower;
/*!
 *
 * Initializes the object with the raw motor values.
 *
 * @param leftMode The left motor mode.
 * @param leftPower A value from 0 to 255 for the power to applied to the motor.
 * @param rightMode The right motor mode.
 * @param rightPower A value from 0 to 255 for the power to applied to the motor.
 * @return Initialized object.
 */
- (id) initWithLeftMode:(RKRawMotorMode) leftMode leftPower:(RKRawMotorPower) leftPower
              rightMode:(RKRawMotorMode) rightMode rightPower:(RKRawMotorPower) rightPower;

@end
