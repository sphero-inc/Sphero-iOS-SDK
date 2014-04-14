//
//  RKAccelerometerData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*!
 * @brief A structure to represent accelerometer values.
 *
 * Structure used to represent acceleration values normalized to 1 g.
 *
 */
struct RKAcceleration {
   float x;
   /*!< The x axis acceleration value. */
   float y;
   /*!< The y axis acceleration value. */
   float z; /*!< The z azis acceleration value. */
};

/*! Type repersenting filtered 3 axis acceleration data */
typedef struct RKAcceleration RKAcceleration;


/*!
 * @brief Class to represent samples of filtered and raw accelerometer data.
 *
 * Class that contains structures to the accelerometer sensor data received from data 
 * streaming. The data can be filtered values and raw values. Data streaming can be set to 
 * return specific axises, so the state structure indicates which values are valid.
 *
 * @sa RKSetDataStreamingCommand.
 */
@interface RKAccelerometerData : RKSensorData {
@private
   RKAcceleration acceleration;
   RK3AxisSensor accelerationRaw;
   RK3AxisSensorState state;
}

/*! Read only property to a structure with the sensor values normailized to 1g. */
@property ( nonatomic, readonly ) RKAcceleration acceleration;
/*! Read only property to a structure with raw data that is represent as integer values 
 * from the sensor. 
 */
@property ( nonatomic, readonly ) RK3AxisSensor accelerationRaw;
/*! Read on property to a state stucture that indicates which sensor data is valid. */
@property ( nonatomic, readonly ) RK3AxisSensorState state;

@end
