//
//  RKRollCommand.h
//  RobotKit
//
//  Created by Brian Smith on 6/15/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>
#import <RobotKit/RKByteCommand.h>

/*! @brief Class to send roll commands to change a robot's heading and speed.
 *
 * Nonmutable class that encapsulates a roll command. This command takes an angle and velocity
 * which the robot uses to stear to this new heading and speed.
 *
 * @sa RKRollResponse
 */
@interface RKRollCommand : RKDeviceCommand {
@private
   float heading;
   float velocity;
   BOOL stop;
}

/*! The angle in degrees set for the heading. */
@property ( nonatomic, readonly ) float heading;
/*! The new velocity for the robot. */
@property ( nonatomic, readonly ) float velocity;
/*! Indicates if this command will stop the robot. */
@property ( nonatomic, assign ) BOOL stop;

/*! 
 * Sends a roll command to the robot for the heading and velocity.
 * @param heading The angle in degrees from 0 to 360 for the robot to head to.
 * @param velocity The velocity from 0.0, no motion, to 1.0, full velocity for the robot
 * to travel at.
 */
+ (void) sendCommandWithHeading:(float) heading velocity:(float) velocity;
/*! 
 * @deprecated
 * Use sendCommandWithHeading:velocity: to change the robot's heading and velocity, and use
 * sendStop for a full stop.
 */
+ (void) sendCommandWithHeading:(float) heading velocity:(float) velocity stopped:(BOOL) state;
/*! Stops the robot in it's tracks */
+ (void) sendStop;
/*! Resend the current heading and velocity values. */
+ (void) resendCurrent;

/*!
 * This sets a velocity that sticks for all instances of RKRollCommand.
 */
+ (void) setStickyVelocity:(float) velocity;
/*!
 * Clears the sticky velocity, so all new instances of RKRollCommand use the velocity parameter.
 */
+ (void) unsetStickyVelocity;
/*!
 * Indicates if an new instance of RKRollCommand will be stuck to a set velocity.
 */
+ (BOOL) isVelocityStuck;
/*!
 * The current heading the robot acknoledged as it's heading.
 */
+ (float) currentHeading;
/*!
 * The current velocity the robot acknowledged as it's velocity.
 */
+ (float) currentVelocity;
/*!
 * Indicates if the robot has acknowledged a full stop.
 */
+ (BOOL) isCurrentlyStopped;

/*!
 * Initializer that sets the heading and velocity for the command. 
 * @sa sendCommandWithHeading:velocity:
 * @param heading The angle in degrees from 0 to 360 for the robot to head to.
 * @param velocity The velocity from 0.0, no motion, to 1.0, full velocity for the robot
 * to travel at.
 * @return The initialized instance.
 */
- (id) initWithHeading:(float) heading velocity:(float) velocity;


@end
