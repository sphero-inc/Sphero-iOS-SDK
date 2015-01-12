//
//  RKGetNonPersistentOptionFlagsCommand.h
//  RobotCommandKit
//
//  Created by Jack Thorp on 8/5/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a get option flags response.
 *
 * This is a simple command that sends a request to return Sphero's current non-persistent option flags
 * Available in Firmware 5.34 or greater
 *
 * @sa RKGetNonPersistentOptionFlagsResponse
 */
@interface RKGetNonPersistentOptionFlagsCommand : RKDeviceCommand

@end
