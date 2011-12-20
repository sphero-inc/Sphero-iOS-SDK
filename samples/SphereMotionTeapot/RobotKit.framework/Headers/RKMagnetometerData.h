//
//  RKMagnetometerData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*!
 *  @brief  Class to contain magnetometer sensor data from data streaming.
 *  
 * Class that contains structures to the magnetometer sensor data received from data 
 * streaming. The data can be filtered values and raw values. Data streaming can be set to 
 * return specific axises, so the state structure indicates which values are valid.
 *
 * @sa RKDeviceSensorsData
 */
@interface RKMagnetometerData : RKSensorData {
    @private
    RK3AxisSensor       magnetometer;
    RK3AxisSensor       magnetometerRaw;
    RK3AxisSensorState  state;
}

/*! The filtered magnetometer 3 axis values. */
@property (nonatomic, readonly) RK3AxisSensor       magnetometer;
/*! The raw magnetometer 3 axis values. */
@property (nonatomic, readonly) RK3AxisSensor       magnetometerRaw;
/*! A structure indicating which axis values are valid. */
@property (nonatomic, readonly) RK3AxisSensorState  state;

@end
