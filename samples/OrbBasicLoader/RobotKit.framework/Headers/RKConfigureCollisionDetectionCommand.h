//
//  RKConfigureCollisionDetectionCommand.h
//  RobotKit
//
//  Created by Brian Smith on 2/23/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceCommand.h"

/*!
 * Constants for the method to use to detect collisions.
 */
enum RKCollisionDetectionMethod {
   /*! Used to turn off collision detection. */
         RKCollisionDetectionMethodDetectionOff = 0,
   /*! Currently this is the only method used to detect collisions. */
         RKCollisionDetectionMethod1 = 1
};
typedef enum RKCollisionDetectionMethod RKCollisionDetectionMethod;


/*!
 * @brief Class that encapsulates a Configure Collision Detection Command.
 *
 * Sphero contains a powerful analysis function to filter accelerometer data in order to detect collisions.
 * Because this is a great example of a high-level concept that humans excel and – but robots do not – a number of
 * parameters control the behavior.  When a collision is detected an asynchronous message is generated to the client.
 *
 * This class allows you to setup the parameters to send to a Sphero to enable collistion detection.
 * You need to register a listener with RKDeviceMessenger to receive the asynchronous data sent after an impact.
 *
 * @sa RKCollisionDetectedAsyncData
 *
 */

@interface RKConfigureCollisionDetectionCommand : RKDeviceCommand {
@private
   RKCollisionDetectionMethod method;
   uint8_t xThreshold;
   uint8_t yThreshold;
   uint8_t xSpeedThreshold;
   uint8_t ySpeedThreshold;
   NSTimeInterval postTimeDeadZone;
}

@property ( nonatomic, readonly ) RKCollisionDetectionMethod method;
@property ( nonatomic, readonly ) uint8_t xThreshold;
@property ( nonatomic, readonly ) uint8_t yThreshold;
@property ( nonatomic, readonly ) uint8_t xSpeedThreshold;
@property ( nonatomic, readonly ) uint8_t ySpeedThreshold;
@property ( nonatomic, readonly ) NSTimeInterval postTimeDeadZone;

/*!
 * Convenience method for sending a robot the command.
 *
 * @param method            The algorithmic method to use for the collision detection. Currently only
 *                          RKCollisionDetectionMethod1 is supported, and you set this to RKCollisionDetectionMethodDetectionOff
 *                          to turn detection off.
 * @param theXThreshold        A threshold value from 0 to 255 to use for the x (right/left) axis.
 * @param theYThreshold        A threshold value from 0 to 255 to use for the y (front/back) axis. The back of Sphero
 *                          is referenced by the back LED. @sa RKBackLEDOutputCommand
 * @param theXSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the xThreshold.
 * @param theYSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the yThreshold.
 * @param deadZone          A value in seconds that indicates a time to wait after detecting an impact before watching
 *                          for the next collision.
 *
 * @deprecated method contains bug where it sends swapped values of yThreshold and xThresholdSpeed to Sphero
 */
+ (void) sendCommandForMethod:(RKCollisionDetectionMethod) method
                   xThreshold:(uint8_t) theXThreshold
                   yThreshold:(uint8_t) theYThreshold
              xSpeedThreshold:(uint8_t) theXSpeedThreshold
              ySpeedThreshold:(uint8_t) theYSpeedThreshold
             postTimeDeadZone:(NSTimeInterval) deadZone;

/*!
 * Convenience method for sending a robot the command.
 *
 * @param method            The algorithmic method to use for the collision detection. Currently only
 *                          RKCollisionDetectionMethod1 is supported, and you set this to RKCollisionDetectionMethodDetectionOff
 *                          to turn detection off.
 * @param theXThreshold        A threshold value from 0 to 255 to use for the x (right/left) axis.
 * @param theXSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the xThreshold.   
 *
 * @param theYThreshold     A threshold value from 0 to 255 to use for the y (front/back) axis. The back of Sphero
 *                          is referenced by the back LED. @sa RKBackLEDOutputCommand
 * @param theYSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the yThreshold.
 * @param deadZone          A value in seconds that indicates a time to wait after detecting an impact before watching
 *                          for the next collision.
 */
+ (void) sendCommandForMethod:(RKCollisionDetectionMethod) method
                   xThreshold:(uint8_t) theXThreshold
              xSpeedThreshold:(uint8_t) theXSpeedThreshold
                   yThreshold:(uint8_t) theYThreshold
              ySpeedThreshold:(uint8_t) theYSpeedThreshold
             postTimeDeadZone:(NSTimeInterval) deadZone;

/*!
 * Convenience method for stoping collision detection.
 */
+ (void) sendCommandToStopDetection;

/**
 * Initializer to set the parameters used to configure the collision detection algorithm.
 *
 * @param method            The algorithmic method to use for the collision detection. Currently only
 *                          RKCollisionDetectionMethod1 is supported, and you set this to RKCollisionDetectionMethodDetectionOff
 *                          to turn detection off.
 * @param theXThreshold        A threshold value from 0 to 255 to use for the x (right/left) axis.
 * @param theYThreshold        A threshold value from 0 to 255 to use for the y (front/back) axis. The back of Sphero
 *                          is referenced by the back LED. @sa RKBackLEDOutputCommand
 * @param theXSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the xThreshold.
 * @param theYSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the yThreshold.
 * @param deadZone          A value in seconds that indicates a time to wait after detecting an impact before watching
 *                          for the next collision.
 * 
 * @deprecated initializer contains bug where it sends swapped values of yThreshold and xThresholdSpeed to Sphero
 */
- (id) initForMethod:(RKCollisionDetectionMethod) method
          xThreshold:(uint8_t) theXThreshold
          yThreshold:(uint8_t) theYThreshold
     xSpeedThreshold:(uint8_t) theXSpeedThreshold
     ySpeedThreshold:(uint8_t) theYSpeedThreshold
    postTimeDeadZone:(NSTimeInterval) deadZone;

/**
 * Initializer to set the parameters used to configure the collision detection algorithm.
 *
 * @param method            The algorithmic method to use for the collision detection. Currently only
 *                          RKCollisionDetectionMethod1 is supported, and you set this to RKCollisionDetectionMethodDetectionOff
 *                          to turn detection off.
 * @param theXThreshold        A threshold value from 0 to 255 to use for the x (right/left) axis.
 * @param theXSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the xThreshold.
 *
 * @param theYThreshold        A threshold value from 0 to 255 to use for the y (front/back) axis. The back of Sphero
 *                          is referenced by the back LED. @sa RKBackLEDOutputCommand
 * @param theYSpeedThreshold   A threshold value from 0 to 255 which gets scaled by the speed and added to the yThreshold.
 * @param deadZone          A value in seconds that indicates a time to wait after detecting an impact before watching
 *                          for the next collision.
 */
- (id) initForMethod:(RKCollisionDetectionMethod) method
          xThreshold:(uint8_t) theXThreshold
     xSpeedThreshold:(uint8_t) theXSpeedThreshold
          yThreshold:(uint8_t) theYThreshold
     ySpeedThreshold:(uint8_t) theYSpeedThreshold
    postTimeDeadZone:(NSTimeInterval) deadZone;

@end
