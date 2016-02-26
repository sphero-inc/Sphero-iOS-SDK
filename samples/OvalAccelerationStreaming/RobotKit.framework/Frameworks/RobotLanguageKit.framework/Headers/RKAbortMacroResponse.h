//
//  Copyright 2014 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <RobotCommandKit/RKDeviceResponse.h>

/*!
 * Codes sent back in the response to an abort macro command.
 */
typedef NS_ENUM(uint8_t, RKAbortMacroCode){
   RKAbortMacroCodeMacroNotRunning = 0 /*!< No macro was running */
};



/*!
 * @brief Class that encapsulates the response from a abort macro command.
 *
 * This is a response that can be used to check for abort codes or see if an error was returned 
 * from an abort macro command.
 *
 * @sa RKAbortMacroCommand
 */

@interface RKAbortMacroResponse : RKDeviceResponse

/*! Read only property for the abort code returned in the response. */
@property ( nonatomic, readonly ) RKAbortMacroCode abortCode;

@end
