//
//  Copyright 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKByteCommand.h"

typedef NS_ENUM(NSInteger, RKRollType) {
   RKRollStop = 0,
   RKRoll = 1,
   RKRollCalibrate = 2
};


/*! @brief Class to send roll commands to change a robot's heading and speed.
 *
 * Nonmutable class that encapsulates a roll command. This command takes an angle and velocity
 * which the robot uses to stear to this new heading and speed.
 *
 * @sa RKRollResponse
 */
@interface RKRollCommand : RKDeviceCommand

/*! The angle in degrees set for the heading. */
@property ( nonatomic, readonly ) float heading;
/*! The new velocity for the robot. */
@property ( nonatomic, readonly ) float velocity;
/*! Indicates if this command will stop the robot. */
@property ( nonatomic, assign ) RKRollType type;

@property ( readwrite) bool reverse;

/*!
 * Initializer that sets the heading and velocity for the command. 
 * @sa sendCommandWithHeading:velocity:
 * @param heading The angle in degrees from 0 to 360 for the robot to head to.
 * @param velocity The velocity from 0.0, no motion, to 1.0, full velocity for the robot
 * to travel at.
 * @return The initialized instance.
 */
- (id) initWithHeading:(float) heading velocity:(float) velocity;

- (id) initAsCalibrateWithHeading:(float) heading;

-(id) initWithByteCommand:(RKByteCommand*) bCommand;

+(id) commandWithHeading:(float) heading andVelocity:(float) velocity;

+(id) commandWithStopAtHeading:(float) heading;


@end
