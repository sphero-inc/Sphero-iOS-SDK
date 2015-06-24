//
//  RKGoToSleepCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 9/9/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! 
 *  Types of sleep
 *  CAUTION: THESE VALUES NEED TO MATCH UNITY OR SLEEP WILL BREAK
 */
typedef NS_ENUM(uint8_t, RKSleepType) {
    RKSleep = 0x00,          // regular sleep - robot advertises at high rate with
    RKSleepDeep = 0x01,
    RKSleepLowPower = 0x02
};

/*! Type to represent the sleep time interval in seconds */
typedef uint16_t RKSleepTimeInterval;


/*!
 * @brief Class that encapsulates a go to sleep command.
 *
 * Class that encapsulates a go to sleep command which can be sent to a
 * robot to have it sleep until the user wakes it or for a given time interval.
 * @sa RKGoToSleepResponse
 *
 * Wakeup  :  The number of seconds for Sphero to sleep for and then automatically reawaken.
              Zero does not program a wakeup interval, so he sleeps forever. FFFFh attempts to put
              him into deep sleep (if supported in hardware) and returns an error if the hardware does not support it.
 * Macro   :  If non-zero, Sphero will attempt to run this macro ID upon wakeup.
 * orbBasic:  If non-zero, Sphero will attempt to run an orbBasic program in Flash from this line number.
 */
@interface RKGoToSleepCommand : RKDeviceCommand

@property ( nonatomic, readonly ) RKSleepTimeInterval wakeUpTimeInterval;
@property ( nonatomic, readonly ) uint8_t  wakeUpMacro;
@property ( nonatomic, readonly ) uint16_t orbBasicLineNumber;
/*!
 * Initializer for the Class which allows for a sleep interval to be set and a system macro to
 * be ran upon waking.
 * @param interval The time in seconds to sleep, or 0 for an indefinite time.
 * @param identifier A system macro id to run upon awaking. This has no effect if the time
 * interval is set to 0.
 */
- (instancetype) initWithWakeUpTimeInterval:(RKSleepTimeInterval) interval macroId:(uint8_t)  identifier;

- (instancetype) initWithWakeUpTimeInterval:(RKSleepTimeInterval) interval orbbasic:(uint16_t) lineNumber;


+ (instancetype) commandWithWakeUpTimeInterval:(RKSleepTimeInterval) interval macroId:(uint8_t)  identifier;

+ (instancetype) commandWithWakeUpTimeInterval:(RKSleepTimeInterval) interval orbbasic:(uint16_t) lineNumber;

+ (instancetype) command;


@end
