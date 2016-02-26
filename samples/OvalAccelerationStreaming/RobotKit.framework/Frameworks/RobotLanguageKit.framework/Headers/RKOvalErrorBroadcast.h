//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOvalErrorBroadcast : RKAsyncMessage

@property (nonatomic) int errorCode;

- (NSString *)errorDescription;

@end
