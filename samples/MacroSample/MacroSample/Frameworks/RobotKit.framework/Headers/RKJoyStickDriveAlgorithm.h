//
//  RKJoyStickDriveAlgorithm.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

#import <RobotKit/RKDriveAlgorithm.h>

/*! @file */

/*!
 *  @brief   A classs for a joy stick style drive control.
 *
 *  This algorithm takes and size that represents an area the 
 *  a joy stick control is dragged in, and converts x and y coordinates in this
 *  area into drive coordinates.  
*/

@interface RKJoyStickDriveAlgorithm : RKDriveAlgorithm {
@private
   CGSize size;
   CGPoint center;
}

/*! Center point of the joy pad area */
@property ( nonatomic, readonly ) CGPoint center;

/*!
 *  Initializes the algorithm with the size of the drag area used for the 
 *  joy stick.
 *  @param size The bounds of area used for the joy stick control.
 *  @return The initialized object.
 */
- (id) initWithPadSize:(CGSize) size;
/*!
 * Updates the size of the screen area used for the joystick.
 * @param size The bounds of the area used for the joystick.
 */
- (void) updatePadSize:(CGSize) size;


@end
