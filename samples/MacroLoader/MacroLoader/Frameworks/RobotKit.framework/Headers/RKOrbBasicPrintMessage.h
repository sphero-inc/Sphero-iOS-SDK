//
//  RKOrbBasicPrintMessage.h
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
@interface RKOrbBasicPrintMessage : RKDeviceAsyncData {
    @private
    NSString *message;
}

/*! The message that was returned from orbBasic for printing on the screen. */
@property (nonatomic, readonly) NSString* message;

@end
