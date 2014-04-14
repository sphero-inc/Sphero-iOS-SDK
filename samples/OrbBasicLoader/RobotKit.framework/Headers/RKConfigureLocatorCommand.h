//
//  RKConfigureLocatorCommand.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/11/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * Constants for the flag option of the Configure Locator Command
 */
enum RKConfigureLocatorFlag {
   /*! Used to turn off locator position system rotates with calibrate */
         RKConfigureLocatorRotateWithCalibrateFlagOff = 0x00,
   /*! Used to turn on locator position system rotates with calibrate */
         RKConfigureLocatorRotateWithCalibrateFlagOn = 0x01
};
/*! Type that is used for setting the data streaming mask */
typedef enum RKConfigureLocatorFlag RKConfigureLocatorFlag;


/*!
 * @brief Class that encapsulates a Configure Locator command (Firmware 1.17 or greater).
 *
 *  Through the streaming interface, Sphero provides real-time location data 
 *  in the form of (X,Y) coordinates on the ground plane. When Sphero wakes up 
 *  it has coordinates (0,0) and heading 0, which corresponds to facing down the 
 *  positive Y-axis. This command allows you to move Sphero to a new location and 
 *  change the alignment of locator coordinates with IMU headings.
 *
 *  When Sphero receives a Set Heading command it changes which real-world direction 
 *  corresponds to heading 0. By default, the locator compensates for this by modifying 
 *  its value for yaw tare. For instance, if you wake up Sphero and drive straight, 
 *  you will be driving down the Y-axis. If you use the Set Heading feature in the 
 *  drive app to turn 90 degrees, you will still have heading 0, but the locator knows 
 *  you have turned 90 degrees and are now facing down the X-axis. This feature can be 
 *  turned off, in which case the locator knows nothing about the Set Heading command. 
 *  This can lead to some strange results. For instance, if you drive using only roll 
 *  commands with heading 0 and set heading commands to change direction the locator 
 *  will perceive your entire path as lying on the Y-axis.
 *
 * @sa RKsetDataStreamingCommand
 * @sa RKLocatorData
 */
@interface RKConfigureLocatorCommand : RKDeviceCommand {

   RKConfigureLocatorFlag configureFlag;
   int16_t positionX;
   int16_t positionY;
   int16_t yawTare;
}

/* The flag rotates the position system with a calibrate when this
   flag is YES, the position systems stays the same when NO */
@property ( nonatomic, readonly ) RKConfigureLocatorFlag configureFlag;
/* The current x position of the device will now be set to this value (in cm) */
@property ( nonatomic, readonly ) int16_t positionX;
/* The current y position of the device will now be set to this value (in cm) */
@property ( nonatomic, readonly ) int16_t positionY;
/* When this is zero, it means device points in the positive x direction
   This may change to point down the y-axis */
@property ( nonatomic, readonly ) int16_t yawTare;

/*!
 * Convenience method for sending a robot the command.
 *
 * @param flag Determines whether calibrate commands automatically correct the yaw tare value. 0 for yes, 1 for no?
 * @param newX (in cm) The new x value that the device will equate the current x value to.
 * @param newY (in cm) The new y value that the device will equate the current y value to.
 * @param newYaw (in degrees) The value will be interpreted in the range 0-359 inclusive.  Controls how the X,Y-plane is aligned 
 *               with Sphero’s heading coordinate system. When this parameter is set to zero, it means that having 
 *               yaw = 0 corresponds to facing down the X- axis in the positive direction.  
 */
+ (void) sendCommandForFlag:(RKConfigureLocatorFlag) flag newX:(int16_t) x newY:(int16_t) y newYaw:(int16_t) yaw;

/**
 * Initializer to set the parameters used to configure the locator.
 *
 * @param flag Determines whether calibrate commands automatically correct the yaw tare value. 0x00 for NO, 0x01 for YES?
 * @param newX (in cm) The new x value that the device will equate the current x value to.
 * @param newY (in cm) The new y value that the device will equate the current y value to.
 * @param newYaw (in degrees) The value will be interpreted in the range 0-359 inclusive.  Controls how the X,Y-plane is aligned 
 *               with Sphero’s heading coordinate system. When this parameter is set to zero, it means that having 
 *               yaw = 0 corresponds to facing down the X- axis in the positive direction.  
 */
- (id) initForFlag:(RKConfigureLocatorFlag) flag newX:(int16_t) x newY:(int16_t) y newYaw:(int16_t) yaw;

@end
