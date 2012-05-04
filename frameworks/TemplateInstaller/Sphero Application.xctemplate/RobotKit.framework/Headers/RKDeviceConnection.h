//
//  RKDeviceConnection.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! @file */

@class RKDeviceConnection;
@class RKRobot;
@class RKDeviceSession;
@protocol RKDeviceConnectionDelegate;


/*!
 * Enumerations for the connection state as communications are established with the
 * robot, and when it goes off line.
 */
enum RKConnectionState {
    RKConnectionStateOffline, /*! The communcation link with a robot is not valid. */
    RKConnectionStateJumpMainApp, /*! The robot is being commanded to go to the main app. */
    RKConnectionStateJumpToBootloader, /*! The robot is being commanded to go to the bootloader. */
    RKConnectionStateMainAppCorrupt, /*! The robot reported a main app corrupt error, and is stuck in the bootloader. */
    RKConnectionStateJumpToBootloaderFailed, /*! Failed to go to bootloader, and is still in the app. */
    RKConnectionStatePing1, /*! A ping was issued to test communications. */
    RKConnectionStatePing2, /*! A second ping issued to test communications before giving up. */
    RKConnectionStateGetBluetoothInfo, /*! A get bluetooth info was sent to the robot. */
    RKConnectionStatePollPacketTimes, /*! Get the packet transmit and receive times for synchronizing clocks. */
    RKConnectionStateOnline /*! The robot is responding to communications and ready for commands to be sent. */
};

/*! Defines a type for connection state enumerations */
typedef enum RKConnectionState RKConnectionState;

/*! @brief A RKDeviceConnection object manages a robot's connection.
 *
 *  A RKDeviceConnection object manages the connection and passing of commands
 *  to a robotic device.
 *  
 *  The sending and receiving of return information is done asynchronously, 
 *  by posting commands to the RKDeviceMessenger shared instance and registering 
 *  to observe response 
 *
 */
@interface RKDeviceConnection : NSObject  {
    @private
    
    RKRobot             *robot;
        
    RKDeviceSession     *session;
            
    NSNumber            *responseTime;
    
    RKConnectionState   connectionState;
    BOOL                startInBootloader;
}

/*! The delegate for the instance */
//@property (nonatomic, assign) id<RKDeviceConnectionDelegate> delegate;
/*! The robot for the connection. */
@property (nonatomic, readonly) RKRobot *robot;
/*! The time to receive a response for the last command sent */
@property (nonatomic, assign) NSNumber  *responseTime;
/*! The count of packets actually sent. */
@property (nonatomic, readonly) NSUInteger packetsSent;
/*! The count of packets received with correct checksums */
@property (nonatomic, readonly) NSUInteger packetsReceived;
/*! The state of the connection. */
@property (nonatomic, readonly) RKConnectionState connectionState;
/*! 
 *  The property overides the default open behavior to start in the main applicaiton
 *  to open starting in the bootloader.
 */
@property (nonatomic, assign) BOOL startInBootloader;

/*! Initializes the connection to the given robot 
 *  @param aRobot The robot to connect to.
 *  @return The initialized RKDeviceConnection instance.
 */
- (id)initWithRobot:(RKRobot *)aRobot;

/*!
 *  Opens communication channels to the robot. Plus, the robot is told to jump
 *  into it's main application, and that it is communicating with the robot. The 
 *  jump to main application can be changed to start in the bootloader using the startInBootloader property. 
 *  A notification is sent to indicate the final state of the connection.
 */
- (void)open;

/*!
 *  Closes the communication channels to the robot.
 */
- (void)close;

@end

/*!
 *  Notification sent when the connection is opened, and messages can be sent
 *  to the ball.
 */
extern NSString * const RKDeviceConnectionOnlineNotification;
/*!
 *  Notification sent when the connection is opened, and messages to the device
 *  
 */
extern NSString * const RKDeviceConnectionOfflineNotification;
/*!
 *  Notification sent when main firmware application is corrupt and can not be run
 *  on the device.
 */
extern NSString * const RKDeviceConnectionMainAppCorruptNotification;
