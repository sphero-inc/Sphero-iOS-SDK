//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*! Mask values that are used to enable the sensor data values that client
 * code is interested in.
 */
typedef NS_OPTIONS(uint64_t, RKDataStreamingMask)  {
   /*! Turns off all data streaming. */
         RKDataStreamingMaskOff = 0x0000000000000000,
   /*! Mask to register for left motor back EMF filtered data */
         RKDataStreamingMaskLeftMotorBackEMFFiltered = 0x0000000000000060,
   /*! Mask to register for right motor back EMF filtered data */
         RKDataStreamingMaskRightMotorBackEMFFiltered = 0x0000000000000060,
   /*! Mask to register for magnetometer z-axis filtered data */
         RKDataStreamingMaskMagnetometerZFiltered = 0x0000000000000080,
   /*! Mask to register for magnetometer y-axis filtered data */
         RKDataStreamingMaskMagnetometerYFiltered = 0x0000000000000100,
   /*! Mask to register for magnetometer x-axis filtered data */
         RKDataStreamingMaskMagnetometerXFiltered = 0x0000000000000200,
   /*! Mask to register for gyro z-axis filtered data */
         RKDataStreamingMaskGyroZFiltered = 0x0000000000000400,
   /*! Mask to register for gyro y-axis filtered data */
         RKDataStreamingMaskGyroYFiltered = 0x0000000000000800,
   /*! Mask to register for gyro x-axis filtered data */
         RKDataStreamingMaskGyroXFiltered = 0x0000000000001000,
   /*! Mask to register for accelerometer z-axis filtered data */
         RKDataStreamingMaskAccelerometerZFiltered = 0x0000000000002000,
   /*! Mask to register for accelerometer y-axis filtered data */
         RKDataStreamingMaskAccelerometerYFiltered = 0x0000000000004000,
   /*! Mask to register for accelerometer x-axis filtered data */
         RKDataStreamingMaskAccelerometerXFiltered = 0x0000000000008000,
   /*! Mask to register for IMU gyro yaw (heading) angle filtered data */
         RKDataStreamingMaskIMUYawAngleFiltered = 0x0000000000010000,
   /*! Mask to register for IMU gyro roll angle filtered data */
         RKDataStreamingMaskIMURollAngleFiltered = 0x0000000000020000,
   /*! Mask to register for IMU gyro pitch angle filtered data */
         RKDataStreamingMaskIMUPitchAngleFiltered = 0x0000000000040000,
   
   /*! Mask to register for left motor back EMF raw data */
         RKDataStreamingMaskLeftMotorBackEMFRaw =  0x0000000000600000,
   /*! Mask to register for right motor back EMF raw data */
         RKDataStreamingMaskRightMotorBackEMFRaw = 0x0000000000600000,
   
   
         RKDataStreamingMaskMotorPWM =  0x00100000 | 0x00080000, // -2048 -> 2047
   
   /*! Mask to register for magnetometer z-axis raw data */
         RKDataStreamingMaskMagnetometer = 0x0000000002000000,

   /*! Mask to register for gyro z-axis raw data */
         RKDataStreamingMaskGyroZRaw = 0x0000000004000000,
   /*! Mask to register for gyro y-axis raw data */
         RKDataStreamingMaskGyroYRaw = 0x0000000008000000,
   /*! Mask to register for gyro x-axis raw data */
         RKDataStreamingMaskGyroXRaw = 0x0000000010000000,
   /*! Mask to register for accelerometer z-axis raw data */
         RKDataStreamingMaskAccelerometerZRaw = 0x0000000020000000,
   /*! Mask to register for accelerometer y-axis raw data */
         RKDataStreamingMaskAccelerometerYRaw = 0x0000000040000000,
   /*! Mask to register for accelerometer x-axis raw data */
         RKDataStreamingMaskAccelerometerXRaw = 0x0000000080000000,
		 RKDataStreamingMaskAccelerometerRaw =  0x00000000E0000000,

   /*! Mask to register for quaternion0 data - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskQuaternion0 = 0x8000000000000000,
   /*! Mask to register for quaternion1 data - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskQuaternion1 = 0x4000000000000000,
   /*! Mask to register for quaternion2 data - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskQuaternion2 = 0x2000000000000000,
   /*! Mask to register for quaternion3 data - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskQuaternion3 = 0x1000000000000000,
   /*! Mask to register for locator streaming of x position - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskLocatorX = 0x0800000000000000,
   /*! Mask to register for locator streaming of y position - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskLocatorY = 0x0400000000000000,

   // TODO:
   //RKDataStreamingMaskAccelOne                  = 0x0200000000000000,

   /*! Mask to register for locator streaming of x velocity - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskVelocityX = 0x0100000000000000,
   /*! Mask to register for locator streaming of y velocity - ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskVelocityY = 0x0080000000000000,

   /*! Convenience mask to register for all gyro filtered data (x, y, z) */
         RKDataStreamingMaskGyroFilteredAll = 0x0000000000001C00,
   /*! Convenience mask to register for all IMU gyro angle filtered data (roll, pitch, yaw) */
         RKDataStreamingMaskIMUAnglesFilteredAll = 0x0000000000070000,
   /*! Convenience mask to register for all filtered accelerometer data (x-axis, y-axis, z-axis) */
         RKDataStreamingMaskAccelerometerFilteredAll = 0x000000000000E000,
   /*! Convenience mask to register for locator streaming of all data (position and velocity)
    * ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskLocatorAll = 0x0D80000000000000,
   /*! Convenience mask to register for locator streaming of all data (position and velocity)
    * ONLY FOR FIRMWARE 1.17 OR GREATER */
         RKDataStreamingMaskQuaternionAll = 0xF000000000000000
};


/*!
 * @brief Class that encapsulates a set data streaming command.
 *
 *  Class that encapsulates a set data streaming command, which allows client code to
 * initiate data streaming of specific sensor data. A mask is used to enable the sensor 
 * data values of interest. The rate in which data can be set a divisor for a sample rate of
 * 400Hz, and a sample frame count can be set that limits packets being sent after this count
 * has been sampled.
 *
 *
 * @sa RKsetDataStreamingCommand
 */
@interface RKSetDataStreamingCommand : RKDeviceCommand

/*! Read only property to the sample rate divisor. */
@property ( nonatomic, readonly ) uint16_t sampleRateDivisor;
/*! Read only property to the sample frame count. */
@property ( nonatomic, readonly ) uint16_t packetFrames;
/*! Read only property to the request mask. */
@property ( nonatomic, readonly ) RKDataStreamingMask requestMask;
/*! Read only property for the number of packets to send */
@property ( nonatomic, readonly ) uint8_t packetCount;

/*! 
 * Keeps track of the current mask being used for streamed data. 
 */
+ (RKDataStreamingMask) currentMask;

/*!
 * Initializer to set up the command.
 */
- (instancetype) initWithSampleRateDivisor:(uint16_t) divisor
                    packetFrames:(uint16_t) frames
                      sensorMask:(RKDataStreamingMask) mask
                     packetCount:(uint8_t) count;

+(instancetype) commandWithStop;
+(instancetype) commandWithRate:(int)hz andMask:(RKDataStreamingMask) mask;

@end
