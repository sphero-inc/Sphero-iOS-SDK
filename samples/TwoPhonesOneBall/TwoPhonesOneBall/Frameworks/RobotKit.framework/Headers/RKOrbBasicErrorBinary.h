//
//  RKOrbBasicErrorBinary.h
//  RobotKit
//
//  Created by Jon Carroll on 3/16/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceAsyncData.h>

/*!
 * Class to encapsulate asyncronous messages sent from a Sphero. To receive this object
 * register as an asynchronous data observer with RKDeviceMessenger.
 */
@interface RKOrbBasicErrorBinary : RKDeviceAsyncData {
    @private
    NSData *errorData;
}

/*! The binary error data returned from the Sphero */
@property (nonatomic, readonly) NSData *errorData;

@end
