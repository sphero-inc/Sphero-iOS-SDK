//
//  RKDeviceResponse_PrivateAdditions.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"

@class RKDeviceCommand;


@interface RKDeviceResponse (PrivateAdditions)

/*!
 *  This class method needs to be overriden by subclasses to return the 
 *  Sphero API command code that the response corrisponds to.
 *  @return The command code.
 */
+ (uint8_t) commandIdentifier;

/*!
 *  This class method needs to be overriden by subclasses to return the device id
 *  that the response belongs to.
 */
+ (uint8_t) deviceIdentifier;


/*!
 *  Used to initialize a subclass based on commparing the command's identifier and 
 *  for with response object's intended command identifier. Subclass should not
 *  override this method.
 *  @param command The original command sent for the response.
 *  @param receiveCode The code returned in the response.
 *  @return The initialized object, or nil if the response object being initialized
 *  does not have the same command identifier.
 */
//- (id) initForCommand:(RKDeviceCommand *) command
//                 code:(NSInteger) receivedCode;
- (id) initWithPacket:(NSData*) packet forCommand:(RKDeviceCommand*) command;

-(id) initAsTimeoutWithCommand:(RKDeviceCommand*) command;

@end
