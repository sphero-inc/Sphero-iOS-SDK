//
//  Copyright 2010-2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>
#import <RobotCommandKit/RobotCommandKit.h>
#import <RobotCommandKit/RKSession.h>

@class RKClassicLink;
/*! @file */

/*! Key used to get the RKRobot object from notifications' userInfo dictionaries. */
extern NSString *const RKRobotKey;

/*!
 *  @brief Represents the robot connection data and physical properties.
 *
 *  A RKRobot object provides the data needed to connect to a robotic data along
 *  physical properties associated with the device.
 */
@interface RKRobotClassic : NSObject < RKRobotBase, RKSessionDelegate, RKLinkDelegate >

@property ( strong, nonatomic ) RKClassicLink *radioLink;

/*! The bluetooth MAC address for the robot */
@property ( strong, nonatomic, readonly ) NSString *bluetoothAddress;

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


- (NSNumber*) signalQuality;

- (void) disconnect;

@end
