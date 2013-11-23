//
//  RKSelfLevelCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/13/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*! Type that is used for setting the self level command options mask */
typedef uint8_t RKSelfLevelCommandOptions;
/*!
 * Constants for the self level command
 *
 * Default behavior or setting these bits to 0 is:
 *
 *                     stop level command (bit 0)
 *                  does not keep heading (bit 1)
 *           stays awake after self level (bit 2)
 *  control system is off after self level(bit 3)
 */
enum {
    /*! Starts the self level command */
    RKSelfLevelCommandOptionStart  = 0x01,
    /*! Rotates to heading equal to beginning heading */
    RKSelfLevelCommandOptionKeepHeading = 0x02,
    /*! Go to sleep after self level command */
    RKSelfLevelCommandOptionSleepAfter = 0x04,
    /*! Turns control system on after calibration */
    RKSelfLevelCommandOptionControlSystemOn = 0x08
};

/*!
 * @brief Class that encapsulates a Self Level Command (Firmware 1.17 or greater).
 *
 *  This command controls the self level routine. The self level routine attempts 
 *  to achieve a horizontal orientation where pitch and roll angles are less than 
 *  the provided Angle Limit. After both angle limits are satisfied, option bits 
 *  control sleep, final angle (heading), and control system on/off. An 
 *  asynchronous message is returned when the self level routine completes.
 *
 *  Default values are: Angle = 2, Timeout = 15, Accuracy = 30 (300 milliseconds)
 * 
 *  Accuracy*10 specifies the number of milliseconds that the pitch and roll angles 
 *  must remain below the Angle Limit after the routine completes. If one of the 
 *  values exceeds the Angle Limit, the ball will self level again 
 *  and the accuracy timer will reset.
 *
 * @sa RKSelfLevelCompleteAsyncData
 */
@interface RKSelfLevelCommand : RKDeviceCommand {
    
    RKSelfLevelCommandOptions levelOptions;
    
    uint8_t levelAngleLimit;
    uint8_t levelTimeout;
    uint8_t levelAccuracy;
}

/* Options mask that controls the behavior of the self level command */
@property (nonatomic, readonly) RKSelfLevelCommandOptions levelOptions;
/*       0: uses the default value in the config block 
   1 to 90: the max angle for completion (in degrees) */
@property (nonatomic, readonly) uint8_t levelAngleLimit;
/*      0: uses the default value in the config block 
 1 to 255: the max seconds to run the routine */
@property (nonatomic, readonly) uint8_t levelTimeout;
/*      0: uses the default value in the config block 
 1 to 255: the accuracy for the routine ot 10*Accuracy (in ms) */
@property (nonatomic, readonly) uint8_t levelAccuracy;

/*!
 * Convenience method to send a self level message to the robotic device.
 * The default self level command has these characteristics:
 * 
 *     - Starts the self level command
 *     - Maintains curent heading
 *     - Stay awake after self level
 *     - Calibration system off after self level
 *
 * An aysnc message will be returned when the self level has completed
 */
+(void)sendCommand;

/*!
 * Convenience method to abort a self level that is currently in progress
 * 
 * What will happen if a self level command is not in progress?
 */
+(void)sendCommandAbortSelfLevel;

/*!
 * Convenience method to send a self level message to the robotic device.
 *
 * @param options bitwise mask flag, see RKSelfLevelCommandOptions enum type
 *
 * @param angleLimit        0: uses the default value in the config block 
 *                    1 to 90: the max angle for completion (in degrees) 
 *
 * @param timeout           0: uses the default value in the config block 
 *                   1 to 255: the max seconds to run the routine
 *  
 * @param accuracy          0: uses the default value in the config block 
 *                   1 to 255: the accuracy for the routine ot 10*Accuracy (in ms)
 */
+(void)sendCommandWithOptions:(RKSelfLevelCommandOptions)options 
                   angleLimit:(uint8_t)angleLimit 
                      timeout:(uint8_t)timeout
                     accuracy:(uint8_t)accuracy;

/* 
 * Initializer to set up the self level command with custom parameters
 */
-(id)initWithOptions:(RKSelfLevelCommandOptions)options 
          angleLimit:(uint8_t)angleLimit 
             timeout:(uint8_t)timeout
            accuracy:(uint8_t)accuracy;

@end
