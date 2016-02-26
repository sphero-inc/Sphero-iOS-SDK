//
//  RKCalibrateCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 6/15/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*!
 * @brief Class to encapsulate a calibrate command and it's parameters.
 * 
 * Class that encapsulates a calibrate command used to set the 0° heading. Client code can 
 * use this along with RKBackLEDOutputCommand and RKRollCommand to aim Sphero so sending a roll
 * command with 0° moves it in a user desired direction. 
 *
 */

__deprecated_msg("replaced by RKSetHeadingCommand")
@interface RKCalibrateCommand : RKDeviceCommand
/*! 
 * The angle that will be added to the current heading when setting
 * the new 0° point. The value is in degrees.
 */
@property ( nonatomic, readonly ) float heading;

/*!
 * Initializer for a RKCalibrateCommand object.
 * @param heading Typically this should be 0.0, but setting it will add to the current heading
 * when setting the new 0° point. The value is in degrees.
 * @return The initialized object.
 */
- (instancetype) initWithHeading:(float) heading;

@end
