//
//  RKControlSystemPresetCommand.h
//  RobotKitLE
//
//  Created by wes on 12/23/13.
//  Copyright (c) 2013 Orbotix. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKControlSystemPresetCommand : RKDeviceCommand

-(id)initWithPreset:(uint8_t) presetId;

+(id)commandWithPreset:(uint8_t) presetId;

@end
