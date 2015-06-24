//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*!
 * @brief Class to encapsulate a set heading command and it's parameters.
 * 
 * Class that encapsulates a calibrate command used to set the 0° heading. 
 * Thus, if you send a Set Heading command with parameter 0, then whichever way Sphero
 * is facing is now 0 degrees.
 *
 * Also, calling this command with Stabilizatoin off, also adjusts Sphero's idea of roll,
 * pitch, and yaw.  The orientation will now be 0,0,0 when the this command is called.
 *
 * @sa RKSetHeadingResponse
 * @sa RKBackLEDOutputCommand
 * @sa RKRollCommand
 */
@interface RKSetHeadingCommand : RKDeviceCommand

/*! 
 * The angle that will be added to the current heading when setting
 * the new 0° point. The value is in degrees.
 */
@property ( nonatomic, readonly ) float heading;

/*!
 * Initializer for a RKSetHeadingCommand object.
 * @param heading Typically this should be 0.0, but setting it will add to the current heading
 * when setting the new 0° point. The value is in degrees.
 * @return The initialized object.
 */
- (instancetype) initWithHeading:(float) heading;

+ (instancetype) commandWithHeading:(float) heading;

+ (instancetype) command;

@end
