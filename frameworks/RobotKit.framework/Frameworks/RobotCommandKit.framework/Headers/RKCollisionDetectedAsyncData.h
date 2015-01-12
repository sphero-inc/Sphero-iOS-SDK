//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import "RKAsyncMessage.h"

/*!
 * Structure to represent acceleration values normalized with the gravity constant. 
 */
struct RKCollisionAcceleration {
   float x;
   float y;
   float z;
};
typedef struct RKCollisionAcceleration RKCollisionAcceleration;

/*!
 * Structure with boolean values for the x and y axes, which is used to indicate the axes of impact.
 */
struct RKCollisionAxis {
   bool x : 1;
   bool y : 1;
};
typedef struct RKCollisionAxis RKCollisionAxis;

/*!
 * Structure with the impact power values for the x and y axes.
 */
struct RKCollisionPower {
   int x;
   int y;
};
typedef struct RKCollisionPower RKCollisionPower;


/**
 *
 * Async data packet sent when Sphero is configured for collision detection, and it detects a collision. Use
 * RKConfigureCollisionDetectionCommand to enable and disable collision notifications.
 *
 * @sa RKConfigureCollisionDetectionCommand
 *
 */

@interface RKCollisionDetectedAsyncData : RKAsyncMessage

/*! Property for the acceleration values at the time of impact. */
@property ( nonatomic, readonly ) RKCollisionAcceleration impactAcceleration;
/*! Property for the axes effected in the impact. */
@property ( nonatomic, readonly ) RKCollisionAxis impactAxis;
/*! Property for the power that occured during impact. */
@property ( nonatomic, readonly ) RKCollisionPower impactPower;
/*! Property that returns the speed at the time of impact. */
@property ( nonatomic, readonly ) float impactSpeed;
/*! Property with a time stamp in the iOS's time reference. */
@property ( nonatomic, readonly ) NSTimeInterval impactTimeStamp;

@end
