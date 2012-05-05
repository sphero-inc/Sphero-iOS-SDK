//
//  RKSetDataStreamingCommand.h
//  RobotKit
//
//  Created by Brian Smith on 7/7/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>

/*! Type that is used for setting the data streaming mask */
typedef uint32_t RKDataStreamingMask;
/*! Mask values that are used to enable the sensor data values that client
 * code is interested in.
 */
enum {
    /*! Turns off all data streaming. */
    RKDataStreamingMaskOff                          = 0x00000000,
    RKDataStreamingMaskLeftMotorBackEMFFiltered     = 0x00000020,
    RKDataStreamingMaskRightMotorBackEMFFiltered    = 0x00000040,
    RKDataStreamingMaskMagnetometerZFiltered        = 0x00000080,
    RKDataStreamingMaskMagnetometerYFiltered        = 0x00000100,
    RKDataStreamingMaskMagnetometerXFiltered        = 0x00000200,
    RKDataStreamingMaskGyroZFiltered                = 0x00000400,
    RKDataStreamingMaskGyroYFiltered                = 0x00000800,
    RKDataStreamingMaskGyroXFiltered                = 0x00001000,
    RKDataStreamingMaskAccelerometerZFiltered       = 0x00002000,
    RKDataStreamingMaskAccelerometerYFiltered       = 0x00004000,
    RKDataStreamingMaskAccelerometerXFiltered       = 0x00008000,
    RKDataStreamingMaskIMUYawAngleFiltered          = 0x00010000,
    RKDataStreamingMaskIMURollAngleFiltered         = 0x00020000,
    RKDataStreamingMaskIMUPitchAngleFiltered        = 0x00040000,
    RKDataStreamingMaskLeftMotorBackEMFRaw          = 0x00200000,
    RKDataStreamingMaskRightMotorBackEMFRaw         = 0x00400000,
    RKDataStreamingMaskMagnetometerZRaw             = 0x00800000,
    RKDataStreamingMaskMagnetometerYRaw             = 0x01000000,
    RKDataStreamingMaskMagnetometerXRaw             = 0x02000000,
    RKDataStreamingMaskGyroZRaw                     = 0x04000000,
    RKDataStreamingMaskGyroYRaw                     = 0x08000000,
    RKDataStreamingMaskGyroXRaw                     = 0x10000000,
    RKDataStreamingMaskAccelerometerZRaw            = 0x20000000,
    RKDataStreamingMaskAccelerometerYRaw            = 0x40000000,
    RKDataStreamingMaskAccelerometerXRaw            = 0x80000000
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
@interface RKSetDataStreamingCommand : RKDeviceCommand {
    uint16_t            sampleRateDivisor;
    uint16_t            packetFrames;
    RKDataStreamingMask requestMask;    
    uint8_t             packetCount;
}

/*! Read only property to the sample rate divisor. */
@property (nonatomic, readonly) uint16_t            sampleRateDivisor;
/*! Read only property to the sample frame count. */
@property (nonatomic, readonly) uint16_t            packetFrames;
/*! Read only property to the request mask. */
@property (nonatomic, readonly) RKDataStreamingMask requestMask;
/*! Read only property for the number of packets to send */
@property (nonatomic, readonly) uint8_t             packetCount;

/*! 
 * Keeps track of the current mask being used for streamed data. 
 */
+ (RKDataStreamingMask)currentMask;

/*!
 * Convenience method to send the message to the robotic device.
 * @param devisor A number to divide the maximum sample rate of 400Hz by. 
 * @param frames The number of sample frames to send in a single packet.
 * @param mask A bitwise OR value of the sensor values to include in data streaming. Set to
 * RKDataStreamingMaskOff or 0 to disable data streaming.
 * @param count Then number of packets that Sphero will send. Set to 0 for infinite data
 * streaming.
 */
+ (void)sendCommandWithSampleRateDivisor:(uint16_t)devisor 
                            packetFrames:(uint16_t)frames 
                              sensorMask:(uint32_t)mask 
                             packetCount:(uint8_t)count;
/*!
 * Initializer to set up the command.
 */
- (id)initWithSampleRateDivisor:(uint16_t)devisor 
                   packetFrames:(uint16_t)frames 
                     sensorMask:(uint32_t)mask 
                      packetCount:(uint8_t)count;

@end
