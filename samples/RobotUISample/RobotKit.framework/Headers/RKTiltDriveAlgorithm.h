//
//  RKTiltDriveAlgorithm.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotKit/RKDriveAlgorithm.h>
#import <UIKit/UIApplication.h>

/*! @file */

/*!
 *  @brief Implementation of tilt bassed drive control from accelerometer data.
 *
 *  Drive Algorithm for using the tilt of the device to control direction and speed
 *  using accelerometer data. The stopOffset property is read as radians from 
 *  the device setting flat.
 */
@interface RKTiltDriveAlgorithm : RKDriveAlgorithm {
@private
   double orientationAngle;
}

/*! Maximum tilt angle in radians used to clamp angle values to */
@property ( nonatomic, readonly ) double maximumTilt;
/*! An angle that represents the yaw orientation of the iOS device. This angle can be used as
 * an offset for the heading.
 */
@property ( nonatomic, assign ) double orientationAngle;

/*!
 * Initializer for the class, which takes the iOS device orientation into account.
 * @param orientation The iOS device orientation.
 * @return The initialized object.
 */
- (id) initWithOrientation:(UIInterfaceOrientation) orientation;

@end
