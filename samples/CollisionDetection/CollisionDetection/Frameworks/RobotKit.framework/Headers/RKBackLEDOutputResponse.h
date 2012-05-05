//
//  RKBackLEDOutputResponse.h
//  RobotKit
//
//  Created by Brian Smith on 6/20/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*!
 * @brief Class that encapsulates the response from a set back LED output command.
 *
 * This is a simple response that can be used to see if an error was returned from a
 * set back LED output.
 *
 * @sa RKBackLEDOutputCommand
 */

@interface RKBackLEDOutputResponse : RKDeviceResponse {
    
}

@end
