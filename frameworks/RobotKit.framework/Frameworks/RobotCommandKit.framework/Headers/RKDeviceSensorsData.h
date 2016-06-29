//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <Foundation/Foundation.h>
#import "RKSensorData.h"
#import "RKSetDataStreamingCommand.h"

@class RKBackEMFData;
@class RKMagnetometerData;
@class RKGyroData;
@class RKAccelerometerData;
@class RKAttitudeData;
@class RKLocatorData;
@class RKQuaternionData;
@class RKMotorData;


/*!
 * @brief Class that represents a sample of sensor data received when streaming data.
 *
 * This class contains objects of various sensor data that is returned for a sample.
 *
 */
@interface RKDeviceSensorsData : RKSensorData

/*! Property for the object that contains a back EMF sample. */
@property ( nonatomic, readonly ) RKBackEMFData *backEMFData;
/*! Property for the object that contains a sample from the magnetometer. */
@property ( nonatomic, readonly ) RKMagnetometerData *magnetometerData;
/*! Property for the object that contains a sample from the gyro sensor */
@property ( nonatomic, readonly ) RKGyroData *gyroData;
/*! Property for the object that contains a sample from the accelerometer */
@property ( nonatomic, readonly ) RKAccelerometerData *accelerometerData;
/*! Property to a RKAttitude object */
@property ( nonatomic, readonly ) RKAttitudeData *attitudeData;
/*! Property to a RKLocator object */
@property ( nonatomic, readonly ) RKLocatorData *locatorData;
/*! Property to a RKQuaternion object */
@property ( nonatomic, readonly ) RKQuaternionData *quaternionData;

@property ( nonatomic, readonly) RKMotorData * motorData;

- (id) initWithMask:(RKDataStreamingMask) mask data:(NSData *) data;

@end
