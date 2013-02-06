//
//  RKDeviceSensorsData.h
//  RobotKit
//
//  Created by Brian Smith on 7/12/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

@class RKBackEMFData;
@class RKMagnetometerData;
@class RKGyroData;
@class RKAccelerometerData;
@class RKAttitudeData;
@class RKLocatorData;
@class RKQuaternionData;

/*!
 * @brief Class that represents a sample of sensor data received when streaming data.
 *
 * This class contains objects of various sensor data that is returned for a sample.
 *
 */
@interface RKDeviceSensorsData : RKSensorData {
    RKBackEMFData       *backEMFData;
    RKMagnetometerData  *magnetometerData;
    RKGyroData          *gyroData;
    RKAccelerometerData *accelerometerData;
    RKAttitudeData      *attitudeData;
    RKLocatorData       *locatorData;
    RKQuaternionData    *quaternionData;
}

/*! Property for the object that contains a back EMF sample. */
@property (nonatomic, readonly) RKBackEMFData       *backEMFData;
/*! Property for the object that contains a sample from the magnetometer. */
@property (nonatomic, readonly) RKMagnetometerData  *magnetometerData;
/*! Property for the object that contains a sample from the gyro sensor */
@property (nonatomic, readonly) RKGyroData          *gyroData;
/*! Property for the object that contains a sample from the accelerometer */
@property (nonatomic, readonly) RKAccelerometerData *accelerometerData;
/*! Property to a RKAttitude object */
@property (nonatomic, readonly) RKAttitudeData      *attitudeData;
/*! Property to a RKLocator object */
@property (nonatomic, readonly) RKLocatorData      *locatorData;
/*! Property to a RKQuaternion object */
@property (nonatomic, readonly) RKQuaternionData      *quaternionData;

@end
