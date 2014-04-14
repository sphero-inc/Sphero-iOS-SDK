//
//  RKMCSPD1.h
//  RobotKit
//
//  Created by Jon Carroll on 10/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

/*!
 *  @brief Sets the system speed 1 variable
 *
 *  This command sets the system speed 1 variable used by roll commands
 *  without a speed.
 *  Allowed values:
 *  speed 0.0-1.0
 */
@interface RKMCSPD1 : RKMacroCommand {
   float speed;
}

/*! The speed associated with the command. 0.0-1.0 allowed. */
@property float speed;

/*! Convenience method for creating a command and setting the parameters in one line.
 *  @param rate The speed to set. 0.0-1.0 allowed.
 *  @return An instance of the command with the given parameters.
 */
+ (RKMCSPD1 *) commandWithSpeed:(float) speed;

@end
