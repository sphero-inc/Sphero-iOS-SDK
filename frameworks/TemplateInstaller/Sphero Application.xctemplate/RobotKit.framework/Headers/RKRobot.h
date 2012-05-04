//
//  RKRobot.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>

/*! @file */

/*!
 *  @brief Represents the robot connection data and physical properties.
 *
 *  A RKRobot object provides the data needed to connect to a robotic data along
 *  physical properties associated with the device.
 */
@interface RKRobot : NSObject {
    @private
    EAAccessory     *accessory;
    NSString        *name;
    NSString        *bluetoothAddress;
    NSTimeInterval  timeOffset;
}

/*! The EAAccessory object that is associated with the robot */
@property (nonatomic, readonly) EAAccessory *accessory;
/*! A product name for the robot */
@property (nonatomic, retain) NSString *name;
/*! The bluetooth MAC address for the robot */
@property (nonatomic, readonly) NSString *bluetoothAddress;

/*! Robot has firmware support for vector command. The default value is NO. */
@property (nonatomic, readonly) BOOL supportsVectorCommand;

/*! The time offset needed to convert the robot's time reference into the iOS device's time reference. */
@property (nonatomic, readonly) NSTimeInterval timeOffset;

/*! 
 *  Initializes with a EAAccesory object for the robot.
 *  @param anAccessory A EAAccesory object for the robot.
 *  @return The initialized RKRobot object or nil if initialization failed.
 */
- (id)initWithAccessory:(EAAccessory *)anAccessory;

/*!
 * Test that the robot object is equal to this robot which means the represent the
 * same device.
 * @param robot The other robot object.
 * @return YES if the other object represents the same robot device. 
 */
- (BOOL)isEqualToRobot:(RKRobot *)robot;

@end
