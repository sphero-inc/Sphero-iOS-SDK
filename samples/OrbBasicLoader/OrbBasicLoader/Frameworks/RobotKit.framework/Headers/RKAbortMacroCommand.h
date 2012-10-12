//
//  RKAbortMacroCommand.h
//  RobotKit
//
//  Created by Brian Smith on 8/30/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RKDeviceCommand.h>

/*!
 * @brief Class to encapsulate a save macro command.
 * 
 * This class is used to send a macro to abort the current running command.
 * 
 * @sa RKAbortMacroResponse
 */
@interface RKAbortMacroCommand : RKDeviceCommand

@end
