//
//  Copyright 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"
#import "RKByteCommand.h"

typedef NS_ENUM(NSInteger, RKRollType) {
   RKRollStop = 0,
	/*! arc drive - standard drive mode */
   RKRoll = 1,
	/*! rotate to requested heading then drive */
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

@property ( nonatomic, strong, readonly ) NSNumber* distanceInCm;

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
- (instancetype) initWithHeading:(float) heading velocity:(float) velocity;

/*! @availability in Sphero FW revision ?.?? (blocked on fw) */
- (instancetype) initWithHeading:(float)heading velocity:(float)velocity andDistance:(float) distance;

- (instancetype) initAsCalibrateWithHeading:(float) heading;

-(instancetype) initWithByteCommand:(RKByteCommand*) bCommand;

+(instancetype) commandWithHeading:(float) heading andVelocity:(float) velocity;

+(instancetype) commandWithHeading:(float) heading velocity:(float) velocity andDistance:(float) distance;

+(instancetype) commandWithStopAtHeading:(float) heading;


@end
