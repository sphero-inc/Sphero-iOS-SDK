//
//  RKLEDOutputResponse.h
//  RobotKit
//
//  Created by Brian Smith on 6/15/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>


/*!
 * @brief Class that encapsulates the response from a set RGB LED command.
 *
 * This is a simple response that can be used to see if an error was returned from a
 * set RGB LED.
 *
 * @sa RKRGBLEDOutputCommand
 */
@interface RKRGBLEDOutputResponse : RKDeviceResponse {
    
}

@end
