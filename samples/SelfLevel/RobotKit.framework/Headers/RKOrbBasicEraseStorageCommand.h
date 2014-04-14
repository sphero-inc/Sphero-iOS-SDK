//
//  RKOrbBasicEraseStorageCommand.h
//  RobotKit
//
//  Created by Jon Carroll on 3/16/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RKDeviceCommand.h>
#import <RobotKit/RKTypes.h>

/*!
 *  This erases any existing program in the specified storage area.
 */
@interface RKOrbBasicEraseStorageCommand : RKDeviceCommand {
@private
   RKOrbBasicStorageType storageType;
}

/*!
 *  Convenience method for sending a command with a particular storage type
 */
+ (void) sendCommandWithStorageType:(RKOrbBasicStorageType) storageType;

/*!
 *  Initialize a command with a particular storage type.
 */
- (id) initWithStorageType:(RKOrbBasicStorageType) storage;

@end
