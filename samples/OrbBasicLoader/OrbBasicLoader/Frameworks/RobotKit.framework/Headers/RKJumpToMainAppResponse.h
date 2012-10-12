//
//  RKJumpToMainAppResponse.h
//  RobotKit
//
//  Created by Brian Smith on 5/31/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*! 
 * @brief Class that encapsulates the response from a jump to bootloader command.
 *
 * A simple response that provides the error code returned from a jump to main app
 * command. An error is returned if the command is sent to the main application or 
 * if the main application is corrupt.
 *
 * @sa RKJumpToBootloaderResponse
 */
@interface RKJumpToMainAppResponse : RKDeviceResponse {

}

@end
