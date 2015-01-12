//
//  RKImmutableCommand.h
//  RobotCommandKit
//
//  Created by Hunter Lang on 6/24/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! @brief Class that represents a completed command, that should not be modified
 *         before being sent to the robot. This is used for completed commands that
 *         come off of the Unity bridge that have their own sequence number encoding
 *         already written into the packet.
 */
@interface RKImmutableCommand : RKDeviceCommand

/*!
 *
 * The initializer for the object which is used to make an immutable command.
 *
 * @param The completed packet of information which should not be modified before being sent
 * @return An immutable command
 */
- (id) initWithPacket:(NSData*) packet;

@end
