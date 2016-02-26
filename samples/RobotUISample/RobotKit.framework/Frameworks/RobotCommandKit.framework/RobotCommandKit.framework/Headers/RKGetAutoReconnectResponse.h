//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"

/*!
 * @brief A response to a RKGetAutoReconnectCommand.
 *
 * Class for the response returned for a get auto reconnect command.
 * 
 * To access the values of the response, call the accessors for 
 * enableFlag and autoReconnectStartTime.
 *
 * @sa RKGetAutoReconnectCommand
 */

@interface RKGetAutoReconnectResponse : RKDeviceResponse {
   BOOL enableFlag;
   uint8_t autoReconnectStartTime;
}

/*! Readonly value to access the enable flag for the command */
@property ( nonatomic, readonly ) BOOL enableFlag;
/*! Readonly value to access the start time of the auto reconnect state */
@property ( nonatomic, readonly ) uint8_t autoReconnectStartTime;

@end
