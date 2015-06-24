//
//  RKLevel1DiagnosticCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 10/14/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotCommandKit/RKDeviceCommand.h>
#import <RobotCommandKit/RKDeviceCommand_PrivateAdditions.h>

/*!
 * @brief Class that encapsulates a request for the robot's level 1 diagnostics.
 *
 * This is a developers-only command to help diagnose aberrant behavior. Upon receipt, active 
 * stabilization is inhibited, all in-process command(macro, helper app, etc.) are terminated 
 * and a special diagnostic program is executed upon the sensor system. There are two responses 
 * to this command: a Simple Response followed by an async stream message containing the 
 * results of the diagnostic tests. To allow flexibility, the results are sent as a long, 
 * human-readable text string. After this command has completed it is up to the developer to 
 * move Sphero from its idle, mindless state into something more useful.
 *
 * This is a simple command that requires no parameters. 
 *
 * @sa RKLevel1DiagnosticResponse
 */

@interface FWLevel1DiagnosticCommand : RKDeviceCommand

+(id) command;

@end
