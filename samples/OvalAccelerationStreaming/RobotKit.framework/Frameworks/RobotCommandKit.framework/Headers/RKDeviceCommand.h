//
//  Copyright 2013 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <Foundation/Foundation.h>
#import "RKDeviceMessage.h"

/*!
 * @brief Base class for commands that can be sent to a robot.
 *
 * This is an abstract class that function as the base class for subclasses which encapsulates
 * the command set of a robot.
 * 
 */
@interface RKDeviceCommand : RKDeviceMessage

@property ( nonatomic, readonly ) NSTimeInterval transmitTimeStamp;
@property (readwrite) BOOL async;
@property (readonly) uint8_t sequenceNumber;

- (BOOL) isAsync;

@end
