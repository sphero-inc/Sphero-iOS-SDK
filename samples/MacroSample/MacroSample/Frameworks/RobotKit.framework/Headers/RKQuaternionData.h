//
//  RKQuaternionAsyncData.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/19/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKSensorData.h"

/*!
 * @brief Structure for Quaternion values.
 * q0 = i axis (1st imaginary component)
 * q1 = j axis (2nd imaginary component)
 * q2 = k axis (3rd imaginary component)
 * q3 = s axis (Real componenet)
 */
struct RKQuaternions {
   float q0;
   /*! Quaternion 0, i axis, Range: -1.0 to 1.0 with units of Q */
   float q1;
   /*! Quaternion 1, j axis, Range: -1.0 to 1.0 with units of Q */
   float q2;
   /*! Quaternion 2, k axis, Range: -1.0 to 1.0 with units of Q */
   float q3; /*! Quaternion 3, s axis, Range: -1.0 to 1.0 with units of Q */
};

/*! Type for a the locator position structure. */
typedef struct RKQuaternions RKQuaternions;

/*!
 * @brief Structure of BOOL values that indicate which quaternion values are valid
 */
struct RKQuaternionState {
   BOOL q0Valid;
   /*! Indicates if the Quaternion 0 is valid */
   BOOL q1Valid;
   /*! Indicates if the Quaternion 1 is valid */
   BOOL q2Valid;
   /*! Indicates if the Quaternion 2 is valid */
   BOOL q3Valid; /*! Indicates if the Quaternion 3 is valid */
};

/*! Type for the Quaternion state structure. */
typedef struct RKQuaternionState RKQuaternionState;


/*!
 * @brief Class to represent sample of Quaternion data
 *
 * Class that contains structures to the quaternion data received from data
 * streaming. Data streaming can be set to return quaternion 0, quaternion 1,
 * quaternion 2, or quaternion 3.  You can stream any and all of these values.
 *
 * @sa RKSetDataStreamingCommand.
 */
@interface RKQuaternionData : RKSensorData {
@private
   RKQuaternionState quaternionState;
   RKQuaternions quaternions;
   NSArray *rotationMatrix;
}


/*! Struct of 4 quaternions */
@property ( nonatomic, readonly ) RKQuaternions quaternions;
/*! Read only property to a structure to use to test which quaternion values are valid */
@property ( nonatomic, readonly ) RKQuaternionState quaternionState;

/*! Converts a quaternion from -10000 to 10000 to -1.0 to 1.0 */
+ (float) nomramlizeWithQuaternion:(int) quaternion;

@end
