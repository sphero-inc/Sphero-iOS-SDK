//
//  RKJumpToBootloaderCommand.h
//  RobotKit
//
//  Created by Brian Smith on 5/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceCommand.h>

/*!
 * @brief Class that encapsulates a jump to bootloader command which can be sent to a
 * robot.
 * 
 * A jump to bootloader command will cause the current app to shutdown and then start the bootloader.
 * @sa RKJumpToBootloaderResponse
 */
@interface RKJumpToBootloaderCommand : RKDeviceCommand {

}

@end
