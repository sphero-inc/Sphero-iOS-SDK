//
//  RKDriveAlgorithm.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! @file */

/*!
 *  @brief Provides the algorithm needed to convert user input to robot coordinates.
 *
 *  Abstract class for use to convert input coordinates to logical device coordinates.
 *  Device coordinates are given by a direction in degrees and a speed from 0.0 
 *  to 1.0. An instance of this needs to be set in RKRobotControl.
 *  @sa RKRobotControl
 */
@interface RKDriveAlgorithm : NSObject {
    @private
    double  angle;
    double  correctionAngle;
    double  velocity;
    double  velocityScale;
    double  stopOffset;
    
    double  windowDeltaForCoord1;
    double  windowDeltaForCoord2;
    double  windowDeltaForCoord3;
    
    id      target;
    SEL     action;
}

/*!
 *  A heading direction calculated by the algorithm in degrees.
 */
@property (nonatomic, assign) double angle;

/*!
 * A correction angle given to the algorithm to modify the heading due to
 * some outside input or event.
 */
@property (nonatomic, assign) double correctionAngle;
 
/*!
 * A speed from 0.0 to 1.0.
 */
@property (nonatomic, assign) double velocity;

/*! A target to send an action to once the conversion completed */
@property (nonatomic, assign) id target;

/*! An action to send once the conversion is completed */
@property (nonatomic, assign) SEL action;

/*!
 * A scale factor from 0.0 to 1.0 which scales the final velocity. The default
 * value is 1.0;
 */
@property (nonatomic, assign) double velocityScale;

/*! 
 *  Value used to offset the stop point.
 */
@property (nonatomic, assign) double stopOffset;

/*! Window delta value for first coordinate */
@property (nonatomic, assign) double windowDeltaForCoord1;

/*! Deadzone delta value for second coordinate */
@property (nonatomic, assign) double windowDeltaForCoord2;

/*! Deadzone delta value for third coordinate */
@property (nonatomic, assign) double windowDeltaForCoord3;


/*!
 * Method that translates the input coordinates to the logical device coordinates.
 * @param coord1 The first coordinate in the input coordinate's space.
 * @param coord2 The second coordinate in the input coordinate's space.
 * @param coord3 The third coordinate in the input coordinate's space.
 */
- (void)convertWithCoord1:(double)coord1 coord2:(double)coord2 coord3:(double)coord3;

/*!
 * Called in subclass once the conversion has finished to notify a target of
 * completed conversion.
 */
- (void)performConversionFinishedAction;

@end
