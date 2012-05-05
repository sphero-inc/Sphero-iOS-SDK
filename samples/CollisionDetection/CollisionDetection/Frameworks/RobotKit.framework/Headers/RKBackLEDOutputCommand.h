//
//  RKBackLEDOutputCommand.h
//  RobotKit
//
//  Created by Brian Smith on 6/20/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>

/*!
 * @brief Class that encapsulates a set back LED output command.
 *
 * This class is used to change the back blue LED brightness on Sphero. The back LED is designed
 * to be inline with the forward direction (0° heading) of Sphero. Thus this can be used to 
 * aid in aiming Sphero (calibration), so a 0° heading set in the roll command goes in the
 * user's prefered direction.
 *
 * @sa RKBackLEDOutputResponse
 */
@interface RKBackLEDOutputCommand : RKDeviceCommand {
    @private
    float   brightness;
}

/*! The brightness value between 0.0 to 1.0 where 0.0 is off and 1.0 is full brightness. */
@property (nonatomic, readonly) float brightness;

/*! 
 * A convenience method for sending the command to the device. 
 * @param brightness The brightness value between 0.0 to 1.0 where 0.0 is off and 1.0 is full brightness.
 */
+ (void)sendCommandWithBrightness:(float)brightness;

/*! 
 * Initializer for a object.
 * @param brightness The brightness value between 0.0 to 1.0 where 0.0 is off and 1.0 is full brightness.
 * @return The initialized object.
 */
- (id)initWithBrightness:(float)brightness;

@end
