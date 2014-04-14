//
//  RKGetOptionFlagsCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a get option flags response.
 *
 * This is a simple command that sends a request to return Sphero's current option flags
 * Available in Firmware 1.18 or greater
 *
 * @sa RKGetOptionFlagsResponse
 */
@interface RKGetOptionFlagsCommand : RKDeviceCommand

@end
