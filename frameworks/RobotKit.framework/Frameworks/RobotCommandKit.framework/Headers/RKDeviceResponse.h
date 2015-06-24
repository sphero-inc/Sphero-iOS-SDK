//
//  Copyright 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceMessage.h"
#import "RKResponseCodes.h"

/*!
 * @brief Abstract class that represents a response for a command.
 *
 * Response objects are created by the framework from response data received for a command sent
 * to a robot. 
 *
 * @sa RKDeviceCommand
 */

@interface RKDeviceResponse : RKDeviceMessage

/*! The response code returned from the robot. */
@property (nonatomic, readonly) RKResponseCode code;
@property (nonatomic, readonly) NSInteger sequenceNumber;

@property (nonatomic, readonly) uint8_t deviceId;
@property (nonatomic, readonly) uint8_t commandId;

- (int8_t) dataLength;

/*! pull response data from raw packet data */
- (NSData*) responseData;

- (BOOL) isError;


@end
