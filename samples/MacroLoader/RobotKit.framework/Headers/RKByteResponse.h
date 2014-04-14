//
//  RKByteResponse.h
//  RobotKit
//
//  Created by Mike DePhillips on 7/9/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>


/*!
 * @brief Class that encapsulates the response from any byte command
 *
 * This is a simple response that can be used to see if an error was returned from the
 * byte command and then also store info to be passed into Unity.
 *
 * @sa RKByteCommand
 */

@interface RKByteResponse : RKDeviceResponse {

}

@end
