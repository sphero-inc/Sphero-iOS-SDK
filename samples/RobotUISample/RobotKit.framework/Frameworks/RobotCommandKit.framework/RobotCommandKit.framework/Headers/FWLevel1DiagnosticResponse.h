//
//  RKLevel1DiagnosticResponse.h
//  RobotKit
//
//  Created by Jon Carroll on 10/14/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotCommandKit/RKDeviceResponse.h>

/*!
 * @brief Class that encapsulates the response from a level 1 diagnostic command.
 * 
 * A simple response that provides the error code from a level 1 diagnostic command. 
 * The level 1 diagnostic data is returned in an asynchronous data packet as human readable
 * ASCII string.
 *
 * @sa RKLevel1DiagnosticCommand
 * @sa RKLevel1DiagnosticAsyncData
 */
@interface FWLevel1DiagnosticResponse : RKDeviceResponse

@end
