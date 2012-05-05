//
//  RKAccelerometerFilter.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <CoreMotion/CoreMotion.h>

/*! @file */

/*!
 * @brief Basic filter object. 
 *
 * Basic definition for accelerometer filters.
 */
@interface RKAccelerometerFilter : NSObject
{
    @private
	BOOL adaptive;
    @protected
    /*! The filtered acceleration data */
	CMAcceleration acceleration;
}

/*!
 *  The filtered acceleration data.
 */
@property(nonatomic, readonly) CMAcceleration acceleration;
/*!
 *  Determines if the if the filter is adaptive. Default value is NO.
 */
@property(nonatomic, getter=isAdaptive) BOOL adaptive;

/*!
 *  Add acceleration data to the filter.
 */
- (void)addAcceleration:(CMAcceleration)accel;


@end

/*!
 *  @brief A filter class to represent a lowpass filter
 * 
 *  A RKLowpassFilter will apply a low pass filtering to the acceleration
 *  data.
 */
@interface RKLowpassFilter : RKAccelerometerFilter
{
    @private
	double filterConstant;
}

/*!
 *  Intializer for the low pass filter.
 *  @param rate The sampling rate used to collect the data.
 *  @param freq The cutoff frequency for the filter.
 */
- (id)initWithSampleRate:(double)rate cutoffFrequency:(double)freq;

@end

/*!
 *  @brief A filter class to represent a highpass filter
 * 
 *  A RKHighpassFilter will apply a high pass filtering to the acceleration
 *  data.
 */
@interface RKHighpassFilter : RKAccelerometerFilter
{
	@private
    double filterConstant;
    CMAcceleration lastAcceleration;
}

/*!
 *  Intializer for the low pass filter.
 *  @param rate The sampling rate used to collect the data.
 *  @param freq The cutoff frequency for the filter.
 */
- (id)initWithSampleRate:(double)rate cutoffFrequency:(double)freq;

@end
