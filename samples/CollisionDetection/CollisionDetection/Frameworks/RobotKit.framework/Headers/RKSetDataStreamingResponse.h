//
//  RKSetDataStreamingResponse.h
//  RobotKit
//
//  Created by Brian Smith on 7/7/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*!
 * @brief Class that encapsulates the response from a set data streaming command.
 *
 * This is a simple response that can be used to see if an error was returned from a
 * set data streaming command. As a convience this Class keeps track of the packetFrame, mask, 
 * and packCount sent in the last successful data streaming command.
 *
 * @sa RKSetDataStreamingCommand
 */
@interface RKSetDataStreamingResponse : RKDeviceResponse {
    
}

/*! Accessor to the packet frames requested in the last sent command. */
+ (NSUInteger)packetFrames;
/*! Accessor to the mask sent in the last sent command. */
+ (NSUInteger)mask;
/*! Accessor the packet count sent in the last sent command. */
+ (NSUInteger)packetCount;

@end
