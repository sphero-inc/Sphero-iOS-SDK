//
//  RKRotationRateCommand.h
//  RobotKit
//
//  Created by Brian Smith on 6/17/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>

/*!
 * @brief Class that encapsulates a set rotation rate command.
 *
 * This class is used to change the rotation rate of Sphero. The rotation rate effects how 
 * sharp Sphero can turn. A low rotation rate means Sphero will make a larger radius of curvature 
 * in a turn, and a higher value will make a smaller radius of curvature, but will be more unstable.
 *
 * @sa RKRotationRateResponse
 */
@interface RKRotationRateCommand : RKDeviceCommand {
@private
   float rate;
}

/*! The rotation rate set for the command. */
@property ( nonatomic, readonly ) float rate;

/*!
 * A convenience method for sending the command.
 * @param rate A value between 0.0 to 1.0 to adjust the rotation rate for the adjustable 
 * range.
 */
+ (void) sendCommandWithRate:(float) rate;

/*!
 * Initializer for the object.
 * @param rate A value between 0.0 to 1.0 to adjust the rotation rate for the adjustable 
 * range.
 * @return The initialized object.
 */
- (id) initWithRate:(float) rate;

@end
