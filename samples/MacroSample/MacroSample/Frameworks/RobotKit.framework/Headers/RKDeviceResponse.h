//
//  RKDeviceResponse.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceMessage.h>
#import <RobotKit/RKResponseCodes.h>

/*!
 * @brief Abstract class that represents a response for a command.
 *
 * Response objects are created by the framework from response data received for a command sent
 * to a robot. Client code can register callbacks with the RKDeviceMessenger singleton to 
 * check error codes and handle parameters received in the response.
 * 
 *
 * @sa RKDeviceCommand
 * @sa RKDeviceMessenger
 */

@interface RKDeviceResponse : RKDeviceMessage {
@protected
   NSInteger sequenceNumber;
   NSInteger code;
   BOOL propertiesValid;
}

/*! The response code returned from the robot. */
@property (nonatomic, readonly) NSInteger code;
@property (nonatomic, readonly) NSInteger sequenceNumber;

@property (nonatomic, readonly) NSInteger deviceId;
@property (nonatomic, readonly) NSInteger commandId;


/*!
 * Indicates that the properties return in the response are valid. The
 * default value is YES. This will get set to NO if the response returned with a error.
 */

@property ( nonatomic, readonly ) BOOL propertiesValid;

- (int8_t) dataLength;

/*! pull response data from raw packet data */
- (NSData*) responseData;


@end
