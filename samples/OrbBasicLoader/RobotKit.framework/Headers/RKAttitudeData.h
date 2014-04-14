//
//  RKIMUData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*! 
 * @brief Structure to indicate which values in RKAttitudeData are valid.
 *
 * Indicates which attitude value are valid based on the mask that was sent 
 * to start the data streaming. 
 */
typedef struct {
   BOOL pitchValid;
   /*!< Indicates if the pitch value is valid. */
   BOOL rollValid;
   /*!< Indicates if the roll value is valid. */
   BOOL yawValid;   /*!< Indicates if the yaw value is valid. */
} RKAttitudeState;


/*!
 *  @brief  Class to contain attitude data from data streaming.
 *  
 * Class that contains structures to the attitude data received from data 
 * streaming. Data streaming can be set to return specific angles, so the state structure 
 * indicates which values are valid.
 *
 * @sa RKDeviceSensorsData
 */
@interface RKAttitudeData : RKSensorData {
   float pitch;
   float roll;
   float yaw;

   RKAttitudeState state;
}

/*! Read only property for the pitch angle of Sphero. */
@property ( nonatomic, readonly ) float pitch;
/*! Read only property for the roll angle of Sphero. */
@property ( nonatomic, readonly ) float roll;
/*! Read only property for the yaw angle of Sphero. */
@property ( nonatomic, readonly ) float yaw;
/*! Read only property to the state structure that indicates which angles are valid numbers. */
@property ( nonatomic, readonly ) RKAttitudeState state;

@end
