//
//  RKTighterControlAddon.h
//  RobotKit
//
//  Created by wes on 4/3/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKit/RobotKit.h>

@interface RKTighterControlAddon : NSObject <RKDriveVectorAddon>

@property ( readwrite ) BOOL enabled;

@end
