//
//  RKDeviceMessage.h
//  RobotKit
//
//  Created by Brian Smith on 5/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceMessageCoding.h>

@protocol RKDeviceMessageCoding;

/*!
 * @brief A base clase for object that messaged to or from a robot.
 *
 * This clase is the base clase for a messages sent and received from a robot. 
 */
@interface RKDeviceMessage : NSObject <RKDeviceMessageCoding> {
	NSTimeInterval timeStamp;
    NSString*      robotId;
}

/*! The time stamp for when an object is created. */
@property (nonatomic, readonly) NSTimeInterval timeStamp;
/*! The unique robot id for the robot that the message pertains to */
@property (nonatomic, readonly) NSString* robotId;

/*! Construct the message with a specific robot id */
- (id) initWithRobotId:(NSString*)anId;

@end
