//
//  RKRobotControlProtocol.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! @file */

/*!
 *  @brief Interface to for classes to implement for controlling a robot.
 * 
 *  This protocol is used to control a robot. It's main responsibility is to provide
 *  high order control methods.
 */

@protocol RKRobotControlProtocol <NSObject>

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

@end
