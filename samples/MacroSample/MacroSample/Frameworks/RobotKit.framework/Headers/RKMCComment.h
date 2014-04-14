//
//  RKMCComment.h
//  RobotKit
//
//  Created by Jon Carroll on 1/27/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKMacroCommand.h"

@interface RKMCComment : RKMacroCommand {
   NSString *comment;
}

@property ( nonatomic, strong ) NSString *comment;

+ (RKMCComment *) commandWithComment:(NSString *) comment;

@end
