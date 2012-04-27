//
//  RKInitMacroExecutive.h
//  RobotKit
//
//  Created by Jon Carroll on 3/2/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RKDeviceCommand.h>

/*!
 *  @brief Terminates running macros and re-initializes the system
 *
 *  This terminates any running macro and reinitializes the macro system. 
 *  The table of any persistent users macros is erased and the storage space is freed.
 *
 */

@interface RKInitMacroExecutiveCommand : RKDeviceCommand

@end
