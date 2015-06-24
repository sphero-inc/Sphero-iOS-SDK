//
//  RKDeviceSensorsAsyncData.h
//  RobotKit
//
//  Created by Brian Smith on 7/7/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKSetDataStreamingCommand.h"
#import <Foundation/Foundation.h>
#import "RKDeviceAsyncData.h"

/*!
 * @brief Class that contains all the sample frames objects from a streaming data packet.
 *
 * Data streaming is inititated using RKSetDataStreamingCommand using a mask to specify the sensor data to send,
 * the rate in which to send data, and the number of samples to send in each packet. This class
 * provides this data in an array of RKDeviceSensorData objects for the sensor data requested.
 *
 * @sa RKSetDataStreamingCommand
 */
@interface RKDeviceSensorsAsyncData : RKAsyncMessage {
@private
	NSUInteger frameCount;
	RKDataStreamingMask mask;
	NSMutableArray *dataFrames;
}

/*! Number of sample frames returned in the packet. */
@property ( nonatomic, readonly ) NSUInteger frameCount;
/*! The mask used to enable what data to include in the data.*/
@property ( nonatomic, readonly ) RKDataStreamingMask mask;
/*! An array of RKDeviceSensorData objects with each sample frame returned. */
@property ( nonatomic, readonly ) NSArray *dataFrames;

@end
