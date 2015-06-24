//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a ping message.
 *
 * This is a simple command that requires no parameters which can be used to test the
 * communication with the robot. 
 *
 * @sa RKPingResponse
 */
@interface RKPingCommand : RKDeviceCommand

+ (instancetype) command;

@end
