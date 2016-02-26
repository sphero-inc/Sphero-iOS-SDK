//
//  RKRotationRateCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 6/17/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a set rotation rate command.
 *
 * This class is used to change the rotation rate of Sphero. The rotation rate effects how 
 * sharp Sphero can turn. A low rotation rate means Sphero will make a larger radius of curvature 
 * in a turn, and a higher value will make a smaller radius of curvature, but will be more unstable.
 *
 * @sa RKRotationRateResponse
 */
@interface RKRotationRateCommand : RKDeviceCommand

/*! The rotation rate set for the command. */
@property ( nonatomic, readonly ) float rate;

/*!
 * Initializer for the object.
 * @param rate A value between 0.0 to 1.0 to adjust the rotation rate for the adjustable 
 * range.
 * @return The initialized object.
 */
- (instancetype) initWithRate:(float) rate;

@end
