//
//  RKOrbBasicExecuteCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 3/16/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceCommand.h>
#import <RobotKit/RKTypes.h>

/*!
 *  This attempts to run a program in the specified storage area beginning at the startingLine number. 
 *  In the event of an error or abort command, the line number specified in cleanupLine is executed 
 *  as a cleanup routine. If zero is specified for the cleanupLine, cleanup is ignored. 
 *  If an error occurs during your cleanup code, Sphero explodes. 
 *  This command will fail if there is already an orbBasic program executing.
 */
@interface RKOrbBasicExecuteCommand : RKDeviceCommand {
    @private
    RKOrbBasicStorageType storageArea;
    unsigned short startLine;
}

/* convenience method to send the command to execute an orb basic program. */
+(void)sendCommandWithStorageArea:(RKOrbBasicStorageType)storageArea startLine:(unsigned short)startLine;

/* Constructs command with given parameters. */
-(id)initWithStorageArea:(RKOrbBasicStorageType)storage startLine:(unsigned short)start;


@end
