//
//  RKPollPacketTimesCommand.h
//  RobotKit
//
//  Created by Brian Smith on 2/24/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Command to request round trip time stamps for time syncing.
 *
 * This command class initiates a communication timing response. It stamps the send time and a 
 * RKPollPacketTimesResponse is returned to a response observer of RKDeviceMessenger. The response contains
 * time stamps for the send and receive of the controller device and robot. These time stamps are then used 
 * to determine time offesets in the devices clocks and delays in communications.
 *
 * @sa RKPollPacketTimesResponse
 * @sa RKDeviceMessenger
 */
@interface RKPollPacketTimesCommand : RKDeviceCommand

@end
