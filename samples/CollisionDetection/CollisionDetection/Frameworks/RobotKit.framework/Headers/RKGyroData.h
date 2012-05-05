//
//  RKGyroData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*!
 *  @brief  Class to contain gyro sensor data from data streaming.
 *  
 * Class that contains structures to the gyro sensor data received from data 
 * streaming. The data can be filtered values and raw values. Data streaming can be set to 
 * return specific axes, so the state structure indicates which values are valid.
 *
 * @sa RKDeviceSensorsData
 */
@interface RKGyroData : RKSensorData {
    @private
    RK3AxisSensor       rotationRate;
    RK3AxisSensor       rotationRateRaw;
    RK3AxisSensorState  state;
}

/*! Read only property for the filtered rotation rate values. */
@property (nonatomic, readonly) RK3AxisSensor       rotationRate;
/*! Read only property for the raw rotation rate values. */
@property (nonatomic, readonly) RK3AxisSensor       rotationRateRaw;
/*! Read only property for the state structure which indicates valid values for the axes. */
@property (nonatomic, readonly) RK3AxisSensorState  state;

@end
