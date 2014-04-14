//
//  Copyright 2013 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>

@class RKRobot;

/*!
 *  @brief Find and Connect to Orbotix Robots.
 *
 *
 */
@interface RKRobotProvider : NSObject <EAAccessoryDelegate>

/*! Available robots. - NOT NECESSARILY CONNECTED */
@property ( nonatomic, readonly , strong) NSMutableArray *robots;

/*! The first connected robot. */
@property ( nonatomic, readonly , strong) RKRobot *robot;

/*! 
 *  Sets the connection to skip jumping to the main application when opening
 *  the connection.
 */
@property ( nonatomic, assign ) BOOL startInBootloader;
/*!
 *  Returns the shared RKRobotProvider object that manages a connected robot.
 *  @return The shared robot provider object.
 */
+ (RKRobotProvider *) sharedRobotProvider;

/*!
 *  Indicates that a user has paired with a robot.
 */
- (BOOL) isRobotAvailable;

/*!
 *  Checks that a robot is being controlled.
 *  @deprecated 
 *  @return YES if a robot is under controlled, otherwise NO.
 */
- (BOOL) isRobotUnderControl;

/*!
 *  Indicates if the robot is connected and communicating.
 *  @return YES if the robot can be communicated with, otherwise NO.
 */
- (BOOL) isRobotConnected;

/*!
 * @deprecated - use connectRobotWithId:(NSString*) id
 * Opens communications with the robot. A RKDeviceConnectionOnlineNotification is
 * posted when the robot has been initialized.
 */
- (void) openRobotConnection;

/*!
 * @deprecated - use disconnectRobotWithId:(NSString*) id
 * Closes communications with the robot.
 */
- (void) closeRobotConnection;

/*!
 *  Method to get control of the connected robot.
 *  @return YES if the a robot was connected and is under control, otherwise
 *  NO if the robot was not connected or can not be controlled.
 *  @deprecated use openRobotConnection instead
 */
- (BOOL) controlConnectedRobot;

/*!
    start of multi ball connectivity- (BOOL) controlRobotAtIndex:(NSUInteger) index
 */
- (RKRobot*) controlRobotAtIndex:(NSUInteger) index;

// TO IMPLEMENT in 2.0
//- (RKRobot*) connectRobotWithId:(NSString*) id;
//- (void)  disconnectRobotWithId:(NSString*) id;

@end

#pragma mark -
#pragma mark String Constants
///*! Key used to get the RKRobotControl object notifications' userInfo dictionaries. */
//extern NSString *const RKRobotControlKey;

#pragma mark -
#pragma mark Notification String Constants
/*! 
 * Notification string posted when a robot becomes available. The userInfo
 * dictionary contains the RKRobot object that is available which is accessed
 * with the RKRobotKey.
 */
extern NSString *const RKRobotIsAvailableNotification; // userinfo: robot
/*!
 * Notification string posted when a robot is no longer available. The userInfo
 * dictionary contains the RKRobot object for the robot that has gone away. This 
 * value is accessed using the RKRobotKey.
 */
extern NSString *const RKRobotIsNoLongerAvailableNotification; // userinfo: robot
/*!
 * Notification string posted when a robot is becomes under control. The userInfo
 * dictionary contains the RKRobot object, which is accessed using the
 * RKRobotControlKey.
 */
extern NSString *const RKRobotDidGainControlNotification; // userinfo: robot
/*!
 * Notification string posted when a robot has lost control.
 */
extern NSString *const RKRobotDidLossControlNotification; // userinfo: nil
/*!
 * Notification string which is used post an NSNotification when a Robot is about to
 * go to sleep. The userInfo dictionary contains the RKRobot object that is going to sleeep.
 */
extern NSString *const RKRobotWillGoToSleepNotification;
