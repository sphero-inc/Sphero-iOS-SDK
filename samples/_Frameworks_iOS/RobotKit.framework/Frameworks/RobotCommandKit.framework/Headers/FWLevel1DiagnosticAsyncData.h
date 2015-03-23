//
//  RKLevel1DiagnosticAsyncData.h
//  RobotKit
//
//  Created by Jon Carroll on 10/14/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotCommandKit/RKAsyncMessage.h>

/*! 
 * @brief Instances of the class contain the data for level 1 diagnostics.
 *
 * The level 1 diagnostic data is a human readable string of data that is returned asynchronously
 * after issuing a RKLevel1DiagnosticCommand.
 *
 * @sa RKLevel1DiagnosticCommand
 */
@interface FWLevel1DiagnosticAsyncData : RKAsyncMessage

/*! A human readable string of the diagnostic data. */
@property (nonatomic, readonly) NSString *diagString;

@end
