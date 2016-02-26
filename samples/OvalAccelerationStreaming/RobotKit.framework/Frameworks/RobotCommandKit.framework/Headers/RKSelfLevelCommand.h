//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

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
typedef NS_ENUM(uint8_t,  RKSelfLevelCommandOptions) {
   /*! Starts the self level command */
         RKSelfLevelCommandOptionStart = 0x01,
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
@interface RKSelfLevelCommand : RKDeviceCommand

/* Options mask that controls the behavior of the self level command */
@property ( nonatomic, readonly ) RKSelfLevelCommandOptions levelOptions;
/*       0: uses the default value in the config block 
   1 to 90: the max angle for completion (in degrees) */
@property ( nonatomic, readonly ) uint8_t levelAngleLimit;
/*      0: uses the default value in the config block 
 1 to 255: the max seconds to run the routine */
@property ( nonatomic, readonly ) uint8_t levelTimeout;
/*      0: uses the default value in the config block 
 1 to 255: the accuracy for the routine ot 10*Accuracy (in ms) */
@property ( nonatomic, readonly ) uint8_t levelAccuracy;

/* 
 * Initializer to set up the self level command with custom parameters
 */
- (instancetype) initWithOptions:(RKSelfLevelCommandOptions) options
            angleLimit:(uint8_t) angleLimit
               timeout:(uint8_t) timeout
              accuracy:(uint8_t) accuracy;

@end
