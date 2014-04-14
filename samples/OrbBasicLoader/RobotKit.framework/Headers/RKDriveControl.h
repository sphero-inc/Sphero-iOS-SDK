//
//  RKDriveControl.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

/*! @file */

@class RKRobotControl;
@class RKRobotProvider;
@class RKRobot;
@class RKAccelerometerFilter;

/*! Drive control types used to in controlling a robot */
typedef enum _RKDriveControlType {
   /*! User sets the RKDriveAlgorithm used by the RKRobotControl object.*/
         RKDriveControlUserDefined,
   /*! Sets a RKJoyStickDriveAlgorithm for the RKRobotControl object.*/
         RKDriveControlJoyStick,
   /*! Used in conjuction with the RKTiltDriveAlgorithm */
         RKDriveControlTilt
} RKDriveControlType;


/*! @brief Singleton class for managing the game play.
 *
 *  This class provides a high level interface for controlling a robot.
 */
@interface RKDriveControl : NSObject {
@private
   CMMotionManager *motionManager;
   NSOperationQueue *motionQueue;
   RKAccelerometerFilter *accelerometerFilter;

   BOOL driving;
   RKDriveControlType driveControlType;
   double velocityScale;
   double stopOffset;
   CGSize joyStickSize;

   BOOL showsRobotLostControlAlert;
}

#pragma mark Object References
/*! The RKRobotProvider object used to manage robots */
@property ( /*weak,*/ nonatomic, readonly ) RKRobotProvider *robotProvider;
/*! The RKRobotControl object from the robotProvider instance */
@property ( /*weak,*/ nonatomic, readonly ) RKRobotControl *robotControl;
/*! The RKRobot object that is being driven */
@property ( /*weak,*/ nonatomic, readonly ) RKRobot *robot;
/*! Instance of the CMMotionManager used to drive the robot */
@property ( nonatomic, readonly ) CMMotionManager *motionManager;

#pragma mark Driving Properties
/*! The driving state. YES if driving, otherwise, NO */
@property ( nonatomic, readonly ) BOOL driving;
/*! Size of the possible values used for a joy stick control */
@property ( nonatomic, assign ) CGSize joyStickSize;
/*! Interface orientation used for tilt control */
@property ( nonatomic, assign ) UIInterfaceOrientation tiltOrientation;
/*! Scale value between 0.0 to 1.0 that scales the velocity of the robot. 
 *  Default value is 1.0.
 */
@property ( nonatomic, assign ) double velocityScale;
/*! 
 * Value used to set a position for the stop point.
 */
@property ( nonatomic, assign ) double stopOffset;
/*! Target to use for action calls */
@property ( /*weak,*/ nonatomic ) id driveTarget;
/*! Action to call once input coordinates are converted to speed and heading
 * for the robot. The method signiture is 
 * - (void)myMethod:(RKDriveAlgorithm *)algorithm.
 * @see RKDriveAlgorithm
 */
@property ( nonatomic, assign ) SEL driveConversionAction;

#pragma mark State Properties
/*! Property to control if Core Motion updates are handled automatically.
 *  Default value is YES.
 */
@property ( nonatomic, assign ) BOOL handlesCoreMotionUpdates;
/*! Property to control the robot lost control alert message */
@property ( nonatomic, assign ) BOOL showsRobotLostControlAlert;


/*! Accessor to the singleton object for this class. 
 * @return The singleton object for this class. 
 */
+ (RKDriveControl *) sharedDriveControl;

/*!
 *  Sets up the game environment. Sets up the resources needed to start controlling
 *  a robot.
 */
- (void) setup;

/*!
 *  Tears down the game environment. Destroys any resources used to control a
 *  robot, and makes sure the robot is shut down properly.
 */
- (void) tearDown;

#pragma mark -
#pragma mark Driving Interface
/*!
 *  Starts driving for a RKDriveControlType. This sets up the drive algorithm
 *  for the given control type. For a Core Motion based control, the updates will
 *  be started unless user disables them first.
 *  @see RKDriveControlType
 *  @see RKRobotControl
 *  @param type The drive control type used to drive.
 */
- (void) startDriving:(RKDriveControlType) type;

/*!
 *  Used to update the robot heading and speed using the point from a joy stick
 *  control.
 *  @param newPoint The new point to use to change the robot's motion. 
 */
- (void) driveWithJoyStickPosition:(CGPoint) newPoint;

/*!
 *  Method to updatre the robot's heading and speed from accelerometer data.
 *  This is called internally for drive types that use accelerometer data.
 *  @param acceleration The acceleration data.
 */
- (void) driveWithAcceleration:(CMAcceleration) acceleration;

/*!
 * Stops driving the robot, which includes stoping Core Motion updates as needed.
 */
- (void) stopDriving;

/*!
 * Uncontrolled boost to give a Sphero enough momentum to go over jumps.
 */
- (void) jump;

@end
