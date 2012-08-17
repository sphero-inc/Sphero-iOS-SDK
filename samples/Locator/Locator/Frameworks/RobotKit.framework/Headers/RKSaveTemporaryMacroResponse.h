//
//  RKSaveTemporaryMacroResponse.h
//  RobotKit
//
//  Created by Brian Smith on 8/17/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RKDeviceResponse.h>

#if defined (SRCLIBRARY)
#import <RobotKit/Macro/RKSaveTemporaryMacroCommand.h>
#else
#import <RobotKit/RKSaveTemporaryMacroCommand.h>
#endif

/*!
 * @brief Class that encapsulates the response from a save temporary macro command.
 *
 * This is a simple response that can be used to see if an error was returned from a
 * save temporary macro command.
 *
 * @sa RKSaveTemporaryMacroCommand
 */

@interface RKSaveTemporaryMacroResponse : RKDeviceResponse {
    @private
    RKMacroFlags macroFlags;
}

/*! The flags that where sent in the original command */
@property (nonatomic, readonly) RKMacroFlags macroFlags;

@end
