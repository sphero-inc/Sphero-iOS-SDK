//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RKDeviceCommand.h>
#import <RobotCommandKit/RKTypes.h>

/*!
 *  This erases any existing program in the specified storage area.
 */
@interface RKOrbBasicEraseStorageCommand : RKDeviceCommand {
@private
   RKOrbBasicStorageType storageType;
}

/*!
 *  Convenience method for sending a command with a particular storage type
 *  moving to compatibility library
 */
//+ (void) sendCommandWithStorageType:(RKOrbBasicStorageType) storageType;

/*!
 *  Initialize a command with a particular storage type.
 */
- (id) initWithStorageType:(RKOrbBasicStorageType) storage;

+(id) commandWithStorageType:(RKOrbBasicStorageType) storage;

@end
