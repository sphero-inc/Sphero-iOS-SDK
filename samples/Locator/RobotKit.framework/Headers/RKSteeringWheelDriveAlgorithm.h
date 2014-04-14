//
//  RKSteeringWheelDriveAlgorithm.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotKit/RKDriveAlgorithm.h>

/*! @file */

/**
 *  @brief Implemention of a steering wheel style algorithm for accelerometer control. 
 *  
 *  An object will convert accelerometer data into heading and speed for driving
 *  a robot ball. 
 *  
 *  The car steering metephor is meant to be a intuitive and familiar control for 
 *  use in a racing type game.
 *
 *  Full stop is considered to be when the z axis perpendicular to the gravity vector, 
 *  |z| = zero, and the x axis is parrellel to the gravity vector, |x| = 1. The 
 *  y accelerometer value is used for direction since it will start at zero.
 */
@interface RKSteeringWheelDriveAlgorithm : RKDriveAlgorithm {
}

@end
