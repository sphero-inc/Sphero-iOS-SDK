//
//  RKJumpToMainAppCommand.h
//  RobotKit
//
//  Created by Brian Smith on 5/31/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>


/*!
 * @brief Class that encapsulates a request for the robot's bootloader to go to the main app.
 *
 * Used to command the bootloader to jump to the main application. The bootloader does jump
 * to the main application, but when it wakes from a deep sleep it will wait which allow this
 * command to force it to jump. The response will contain an error if the command is sent to
 * main app.
 *
 * This is a simple command that requires no parameters. 
 *
 * @sa RKJumpToMainAppResponse
 */

@interface RKJumpToMainAppCommand : RKDeviceCommand {

}

@end
