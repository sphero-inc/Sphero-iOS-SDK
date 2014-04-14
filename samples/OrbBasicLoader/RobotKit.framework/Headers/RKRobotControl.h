//
//  RKRobotControl.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>
#import <CoreMotion/CoreMotion.h>
#import <RobotKit/RKDeviceConnection.h>
#import <RobotKit/RKRobotControlProtocol.h>

/*! @file */

@class RKRobot;
@class RKDeviceConnection;
@class RKDriveAlgorithm;


/*!
 *  @brief Objects of this class use a connection to manipulating a robot.
 * 
 *  This class is used to control a robot. It's main responsibility is to 
 *  high order control methods like converting input coordinates to robotic
 *  coordinates to send to the device.
 */
@interface RKRobotControl : NSObject
      <RKRobotControlProtocol, EAAccessoryDelegate, NSStreamDelegate> {
@private
   RKDeviceConnection *deviceConnection;
   RKDriveAlgorithm *driveAlgorithm;

   BOOL inDeadZone;
   float deadZoneSize;

   BOOL calibrating;

   float boostTimeScale;
   float controlledBoostVelocity;
   BOOL uncontrolledBoost;
   BOOL controlledBoost;


}

/*! Readonly property for the robot that is being controlled.*/
@property ( weak, nonatomic, readonly ) RKRobot *robot;

/*! Accessor to the RKDeviceConnection for calling direct commands to the device */
@property ( nonatomic, readonly ) RKDeviceConnection *deviceConnection;

/*! Property to set and access the drive algorithm. A RKSteeringWheelDriveMethod
 *  is created by default.
 *  @see RKDriveAlgorithm 
 */
@property ( nonatomic, strong ) RKDriveAlgorithm *driveAlgorithm;

/*! Provides a deadzone in terms of a fraction of full velocity. */
@property ( nonatomic, assign ) float deadZoneSize;

/*! Property for setting an offset to adjust what is consider a stop point
 *  for the input. Depends on the drive method used.
 *  @sa RKDriveMethod
 */
@property ( nonatomic, assign ) double stopOffset;

/*!
 * The fraction of 25.5 seconds for a boost. Default value is 1.0.
 * @sa jump
 */
@property ( nonatomic, assign ) float boostTimeScale;

/*! Property for assigning a velocity for controlled boosts. */
@property ( nonatomic, assign ) float controlledBoostVelocity;


/*!
 * Property for clients to check that the robot is being calibrated.
 * @return YES if the robot is being calibrated, otherwise NO if in normal mode.
 */
@property ( nonatomic, readonly ) BOOL calibrating;

/*! 
 *  Initializer that setups control of a robot.
 *  @param aRobot   The RKRobot instance to control.
 *  @return The initialized instance or nil if the robot can't be controlled.
 */
- (id) initWithRobot:(RKRobot *) aRobot;

/*!
 * Stops the device from moving.
 */
- (void) stopMoving;

/*!
 *  Method used to drive a robot with a set coordinates. Coordinates are
 *  unspecified as the can be angular or scaler coordinates. The coordinates are
 *  dependent on the drive method used.
 *  @param  coord1 The first parameter in the coordinate system.
 *  @param  coord2 The second parameter in the coordinate system.
 *  @param  coord3 The third parameter in the coordinate system.
 */
- (void) driveWithCoord1:(double) coord1 coord2:(double) coord2 coord3:(double) coord3;

/*!
 *  Starts the calibration mode for Sphero. This mainly sets up the 
 *  calibration LED.
 */
- (void) startCalibration;

/*!
 *  Stop calibration mode for Sphero. 
 *  @param calibrate YES to calibrate for new heading, and NO to stop calibration
 *  without setting calibration on the ball.
 */
- (void) stopCalibrated:(BOOL) calibrate;

/*!
 *  Method to rotate Sphero to a heading without moving the ball. Used during
 *  calibration.
 *  @param angle A heading angle between 0° to 360°
 */
- (void) rotateToHeading:(float) angle;

/*!
 *  Tells the robot to move in the direction given by the angle, and at a
 *  given velocity. This method will honor the dead zone.
 *  @param angle The direction given by an angle between 0° and 360°.
 *  @param velocity A velocity between 0.0 and 1.0.
 */
- (void) rollAtHeading:(float) angle velocity:(float) velocity;

/*!
 *  Tells the robot to move at the given velocity for the boost time.
 *  During the time interval, the user can control
 *  the robot's direction but the velocity is fixed.
 */
- (void) startControlledBoost;

/*!
 *  Cancels the currently running controlled boost so that the velocity is no
 *  longer stuck at the boosted level. This command is only effective if the
 *  robot is currently in a controlled boost mode.
 */
- (void) cancelControlledBoost;

/*!
 *  Resets the dead zone to the default value.
 */
- (void) resetDeadZoneSize;

/*!
 * Uncontrolled boost to give a Sphero enough momentum to go over jumps.
 */
- (void) jump;

@end


/*! Notification constant for when a boost has finished. */
extern NSString *const RKRobotBoostDidFinishNotification;

