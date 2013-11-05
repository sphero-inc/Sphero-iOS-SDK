//
//  RKCalibrateCommand.h
//  RobotKit
//
//  Created by Brian Smith on 6/15/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <Robotkit/RKDeviceCommand.h>

/*!
 * @brief Class to encapsulate a calibrate command and it's parameters.
 * 
 * Class that encapsulates a calibrate command used to set the 0° heading. Client code can 
 * use this along with RKBackLEDOutputCommand and RKRollCommand to aim Sphero so sending a roll
 * command with 0° moves it in a user desired direction. 
 *
 * @sa RKCalibrateResponse
 * @sa RKBackLEDOutputCommand
 * @sa RKRollCommand
 *
 * @deprecated Replacd by @sa RKSetHeadingCommand
 */
@interface RKCalibrateCommand : RKDeviceCommand {
@private
   float heading;
}

/*! 
 * The angle that will be added to the current heading when setting
 * the new 0° point. The value is in degrees.
 */
@property ( nonatomic, readonly ) float heading;

/*! 
 * Convenience method for sending the command through RKDeviceMessenger.
 * @param heading Typically this should be 0.0, but setting it will add to the current heading
 * when setting the new 0° point. The value is in degrees.
 */
+ (void) sendCommandWithHeading:(float) heading;
/*!
 * Initializer for a RKCalibrateCommand object.
 * @param heading Typically this should be 0.0, but setting it will add to the current heading
 * when setting the new 0° point. The value is in degrees.
 * @return The initialized object.
 */
- (id) initWithHeading:(float) heading;

@end
