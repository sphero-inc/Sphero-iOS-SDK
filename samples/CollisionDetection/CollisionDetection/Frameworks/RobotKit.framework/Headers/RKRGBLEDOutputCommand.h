//
//  RKLEDOutputCommand.h
//  RobotKit
//
//  Created by Brian Smith on 6/15/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <Robotkit/RKDeviceCommand.h>

/*!
 * @brief Class that encapsulates a set RGB LED output command.
 *
 * This class is used to change the red, green, blue brightness of the RGB LED on a Sphero.
 *
 * @sa RKRGBLEDOutputResponse
 */
@interface RKRGBLEDOutputCommand : RKDeviceCommand {
    @private
    float red;
    float green;
    float blue;
}

/*! The red brightness that is sent with the command. */
@property (nonatomic, readonly) float red;
/*! The green brightness that is sent with the command. */
@property (nonatomic, readonly) float green;
/*! The blue brightness that is sent with the command. */
@property (nonatomic, readonly) float blue;

/*!
 * Convience method for sending the command to the device. 
 * @param red The red brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being 
 * full brightness.
 * @param green The green brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being
 * full brightness.
 * @param blue The blue brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being
 * full brightness.
 */
+ (void)sendCommandWithRed:(float)red green:(float)green blue:(float)blue;

/*! The current RGB LED red value that was successfully sent to the device. */
+ (float)currentRed;
/*! The current RGB LED green value that was successfully sent to the device. */
+ (float)currentGreen;
/*! The current RGB LED blue value that was successfully sent to the device. */
+ (float)currentBlue;

/*!
 * Initializer for the object.
 * @param red The red brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being 
 * full brightness.
 * @param green The green brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being
 * full brightness.
 * @param blue The blue brightness value between 0.0 to 1.0 with 0.0 being off and 1.0 being
 * full brightness.
 * @return The initialized object.
 */
- (id)initWithRed:(float)red green:(float)green blue:(float)blue;

@end
