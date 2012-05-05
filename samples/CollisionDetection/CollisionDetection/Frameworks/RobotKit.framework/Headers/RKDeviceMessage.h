//
//  RKDeviceMessage.h
//  RobotKit
//
//  Created by Brian Smith on 5/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>

/*!
 * @brief A base clase for object that messaged to or from a robot.
 *
 * This clase is the base clase for a messages sent and received from a robot. 
 */
@interface RKDeviceMessage : NSObject {
	NSTimeInterval timeStamp;
}

/*! The time stamp for when an object is created. */
@property (nonatomic, readonly) NSTimeInterval timeStamp;

@end
