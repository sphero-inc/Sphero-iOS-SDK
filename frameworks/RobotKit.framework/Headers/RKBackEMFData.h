//
//  RKBackEMFData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*!
 * @brief Structure for back EMF values.
 *
 * Structure with the right and left back EMF values.
 */
struct RKBackEMF {
   int16_t rightMotor;
   /*!< The right motor value of the back EMF */
   int16_t leftMotor;  /*!< The left motor value of the back EMF */
};

/*! Type for a the back EMF structure. */
typedef struct RKBackEMF RKBackEMF;

/*!
 * @brief Structure of BOOL values that indicate which back EMF values are valid
 * Structure whose members indicate which of the filtered and raw back EMF values are valid.
 */
struct RKBackEMFState {
   BOOL rightMotorValid;
   /*!< Indicates if the right motor value is valid. */
   BOOL leftMotorValid;
   /*!< Indicates if the left motor value is valid. */
   BOOL rightMotorRawValid;
   /*!< Indicates if the right motor value is valid. */
   BOOL leftMotorRawValid; /*!< Indicates if the left motor value is valid. */
};

/*! Type for the back EMF state structure. */
typedef struct RKBackEMFState RKBackEMFState;


/*!
 * @brief Class to represent samples of filtered and raw accelerometer data.
 *
 * Class that contains structures to the accelerometer sensor data received from data 
 * streaming. The data can be filtered values and raw values. Data streaming can be set to 
 * return specific axises, so the state structure indicates which values are valid.
 *
 * @sa RKSetDataStreamingCommand.
 */
@interface RKBackEMFData : RKSensorData {
@private
   RKBackEMF backEMF;
   RKBackEMF backEMFRaw;
   RKBackEMFState state;
}

/*! Read only property to access the filtered back EMF values. */
@property ( nonatomic, readonly ) RKBackEMF backEMF;
/*! Read only property to access the filtered back EMF values. */
@property ( nonatomic, readonly ) RKBackEMF backEMFRaw;
/*! Read only property to a structure to use to test which back EMF values are valid */
@property ( nonatomic, readonly ) RKBackEMFState state;

@end
