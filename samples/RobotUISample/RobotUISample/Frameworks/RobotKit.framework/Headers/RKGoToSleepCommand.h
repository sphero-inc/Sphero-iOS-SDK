//
//  RKGoToSleepCommand.h
//  RobotKit
//
//  Created by Brian Smith on 9/9/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! Type to represent the sleep time interval in seconds */
typedef uint16_t RKSleepTimeInterval;

/*!
 * @brief Class that encapsulates a go to sleep command.
 *
 * Class that encapsulates a go to sleep command which can be sent to a
 * robot to have it sleep until the user wakes it or for a given time interval.
 * @sa RKGoToSleepResponse
 */
@interface RKGoToSleepCommand : RKDeviceCommand {
    @private
    RKSleepTimeInterval wakeUpTimeInterval;
    uint8_t             wakeUpMacro;
}

/*!
 * Convience method that creates a RKGoToSleepCommand instance and uses RKDeviceMessenger to 
 * send the command to the robot.
 * @param interval The time in seconds to sleep, or 0 for an indefinite time.
 * @param identifier A system macro id to run upon awaking. This has no effect if the time
 * interval is set to 0.
 */
+ (void)sendCommandWithWakeUpTimeInterval:(RKSleepTimeInterval)interval macroId:(uint8_t)identifier;
/*!
 * Initializer for the Class which allows for a sleep interval to be set and a system macro to
 * be ran upon waking.
 * @param interval The time in seconds to sleep, or 0 for an indefinite time.
 * @param identifier A system macro id to run upon awaking. This has no effect if the time
 * interval is set to 0.
 */
- (id)initWithWakeUpTimeInterval:(RKSleepTimeInterval)interval macroId:(uint8_t)identifier;

@end
