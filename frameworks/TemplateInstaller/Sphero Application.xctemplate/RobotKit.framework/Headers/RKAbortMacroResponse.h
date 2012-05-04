//
//  RKAbortMacroResponse.h
//  RobotKit
//
//  Created by Brian Smith on 8/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */
#import "RKDeviceResponse.h"

/*!
 * Codes sent back in the response to an abort macro command.
 */
enum RKAbortMacroCode {
    RKAbortMacroCodeMacroNotRunning = 0 /*!< No macro was running */
};

/*!
 * Defines a RKAbortMacroCode type for macro abort codes.
 */
typedef enum RKAbortMacroCode RKAbortMacroCode;

/*!
 * @brief Class that encapsulates the response from a abort macro command.
 *
 * This is a response that can be used to check for abort codes or see if an error was returned 
 * from an abort macro command.
 *
 * @sa RKAbortMacroCommand
 */

@interface RKAbortMacroResponse : RKDeviceResponse {
    RKAbortMacroCode abortCode;
}

/*! Read only property for the abort code returned in the response. */
@property (nonatomic, readonly) RKAbortMacroCode abortCode;

@end
