//
//  RKByteCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 6/27/13.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Class that encapsulates a raw byte command to send to the ball.
 *
 * Only use this class if you know how to form a proper command per the Sphero API doc
 */
@interface RKByteCommand : RKDeviceCommand

/*! 
 * 
 * The initializer for the object which is used to make a byte command.
 *
 * @param packet the properly formatted raw bytes of a Sphero command.
 * @return The initialized object.
 */
- (id) initWithPacket:(NSData*) packet;

@end
