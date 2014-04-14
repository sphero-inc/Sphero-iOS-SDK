//
//  RKNonPersistentOptionsFlagCommand.h
//  RobotKit
//
//  Created by wes felteau on 4/16/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>

@interface RKNonPersistentOptionsFlagCommand : RKDeviceCommand

+ (void) sendRead;

/*! Enable Stop On Disconnect behavior: When the Bluetooth link transitions from connected to disconnected, Sphero is commanded to stop rolling. This is ignored if a macro or orbBasic program is running though both have option flags to allow this during their execution. This flag is cleared after it is obeyed, thus it needs to be re-enabled upon every connect of a Robot if necessary.
 */
+ (void) sendSetStopOnDisconnectCommand;

@end
