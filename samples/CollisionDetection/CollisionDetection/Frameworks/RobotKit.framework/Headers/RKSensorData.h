//
//  RKSensorData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>

/*!
 * @brief A structure that represents data values from a 3 axis sensor.
 *
 * A structure that represents data values from a 3 axis sensor. The value range is dependent on
 * the sensor. For example, an accelerometer sensor may be a signed 12 bit value whose values
 * are in the range of plus or minus 3g.
 */
struct RK3AxisSensor {
    int16_t x; /*!< The x axis value of the sensor. */
    int16_t y; /*!< The y axis value of the sensor. */
    int16_t z; /*!< The z axis value of the sensor. */
};

/*!
 * Defines a RK3AxisSensor type from a RK3AxisSensor structure.
 */
typedef struct RK3AxisSensor RK3AxisSensor;

/*!
 * 
 * @brief A structure used to indicate which sensor values are valid from streamed data.
 *
 * This type is a structure of boolean flags to indicate which sensor data values
 * are valid. Each flag is set based on a mask used to request streaming data, which
 * allows control down to a paticular axis to be sampled.
 */
struct  RK3AxisSensorState {
    BOOL xValid; /*!< Indicates that the filtered x axis sensor value is valid. */
    BOOL yValid; /*!< Indicates that the filtered y axis sensor value is valid. */
    BOOL zValid; /*!< Indicates that the filtered z axis sensor value is valid. */
    BOOL xRawValid; /*!< Indicates that the raw x axis sensor value is valid. */
    BOOL yRawValid; /*!< Indicates that the raw y axis sensor valie is valid. */
    BOOL zRawValid; /*!< Indicates that the raw z axis sensor value is valid. */
};

/*!
 * Defines a RK3AxisSensorState type from a RK3AxisSensorState structure.
 */
typedef struct RK3AxisSensorState RK3AxisSensorState;

/*!
 * @brief Base class for all sensor data classes.
 *
 * Provides a base class for various sensor data sub classes. The sensor data is 
 * provided from samples returned from data streaming.
 */
@interface RKSensorData : NSObject {
    NSTimeInterval  timeStamp;
}

/*! A timestamp that is set in the objects initializer for when the object is created. */
@property (nonatomic, readonly) NSTimeInterval timeStamp;

@end
