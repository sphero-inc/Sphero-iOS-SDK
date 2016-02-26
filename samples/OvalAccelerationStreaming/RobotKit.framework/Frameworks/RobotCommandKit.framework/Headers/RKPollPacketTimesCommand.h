//
//  RKPollPacketTimesCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 2/24/12.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Command to request round trip time stamps for time syncing.
 *
 * This command class initiates a communication timing response.  The response contains
 * time stamps for the send and receive of the controller device and robot. These time stamps are then used 
 * to determine time offesets in the devices clocks and delays in communications.
 *
 * @sa RKPollPacketTimesResponse
 */
@interface RKPollPacketTimesCommand : RKDeviceCommand

@end
