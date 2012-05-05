//
//  RKRollResponse.h
//  RobotKit
//
//  Created by Brian Smith on 6/15/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*!
 * @brief Class that encapsulates the response from a roll command.
 *
 * This is a simple response that can be used to see if an error was returned from a
 * roll command. The original command's heading and velocity are accessable 
 *
 * @sa RKRollCommand
 */
@interface RKRollResponse : RKDeviceResponse {
    float velocity;
    float heading;
}

/*! Property for the velocity that was sent in the response's command */
@property float velocity;
/*! Property for accesss the heading that was sent in the response's command */
@property float heading;

@end
