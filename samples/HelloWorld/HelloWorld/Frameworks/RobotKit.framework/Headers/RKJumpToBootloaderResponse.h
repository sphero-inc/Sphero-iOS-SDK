//
//  RKJumpToBootloaderResponse.h
//  RobotKit
//
//  Created by Brian Smith on 5/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*! 
 * @brief Class that encapsulates the response from a jump to main application command.
 *
 * A simple response that provides the error code returned from a jump to bootloader
 * command. Typically this is sent to the main application and a RKResponseCodeOK value will
 * be returned before the jump. An error will be returned if this is sent to the bootloader.
 * Client code should delay any calls to the bootloader to allow it to initialize.
 *
 * @sa RKJumpToBootloaderResponse
 */
@interface RKJumpToBootloaderResponse : RKDeviceResponse {
}

@end
