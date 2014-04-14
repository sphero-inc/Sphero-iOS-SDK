//
//  RKRobot.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>
#import "RKDeviceConnection.h"

/*! @file */



/*! Key used to get the RKRobot object from notifications' userInfo dictionaries. */
extern NSString *const RKRobotKey;


/*!
 *  @brief Represents the robot connection data and physical properties.
 *
 *  A RKRobot object provides the data needed to connect to a robotic data along
 *  physical properties associated with the device.
 */
@interface RKRobot : NSObject


/*! A product name for the robot */
@property ( strong, nonatomic) NSString *name;


/*! The EAAccessory object that is associated with the robot */
@property ( strong, nonatomic, readonly ) EAAccessory *accessory;

/*! The bluetooth MAC address for the robot */
@property ( strong, nonatomic, readonly ) NSString *bluetoothAddress;

// todo - make private
@property ( strong, nonatomic ) RKDeviceConnection *connection;


/*! Robot has firmware support for vector command. The default value is NO. */
@property ( nonatomic, readonly ) BOOL supportsVectorCommand;

/*! The time offset needed to convert the robot's time reference into the iOS device's time reference. */
@property ( nonatomic, readonly ) NSTimeInterval timeOffset;

/*! User color of RGB that is remembered even when Sphero is turned on and off */
@property ( nonatomic, assign ) float userColorRedIntensity;
@property ( nonatomic, assign ) float userColorGreenIntensity;
@property ( nonatomic, assign ) float userColorBlueIntensity;


/*!
 *  Initializes with a EAAccesory object for the robot.
 *  @param anAccessory A EAAccesory object for the robot.
 *  @return The initialized RKRobot object or nil if initialization failed.
 */
- (id) initWithAccessory:(EAAccessory *) anAccessory;

/*!
 * Test that the robot object is equal to this robot which means the represent the
 * same device.
 * @param robot The other robot object.
 * @return YES if the other object represents the same robot device. 
 */
- (BOOL) isEqualToRobot:(RKRobot *) robot;

- (BOOL) connect;
- (void) disconnect;

- (BOOL) isBluetoothConnected;

@end
