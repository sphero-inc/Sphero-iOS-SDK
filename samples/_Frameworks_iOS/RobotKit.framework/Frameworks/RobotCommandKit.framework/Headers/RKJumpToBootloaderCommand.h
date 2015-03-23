//
//  RKJumpToBootloaderCommand.h
//  RobotCommandKit
//
//  Created by Brian Smith on 5/30/11.
//  Imported to RobotCommandKit by Hunter Lang on 12/12/13.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceCommand.h"

/*!
 * @brief Class that encapsulates a jump to bootloader command which can be sent to a
 * robot.
 * 
 * A jump to bootloader command will cause the current app to shutdown and then start the bootloader.
 * @sa RKJumpToBootloaderResponse
 */
@interface RKJumpToBootloaderCommand : RKDeviceCommand

+(instancetype) command;

@end
