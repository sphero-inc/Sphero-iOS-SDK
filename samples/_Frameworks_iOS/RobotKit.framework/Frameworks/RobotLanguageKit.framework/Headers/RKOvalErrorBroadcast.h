//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>
#import <OvalCompiler/ovmlanguage.h>

@interface RKOvalErrorBroadcast : RKAsyncMessage

@property (nonatomic) enum OvmErrorCodes errorCode;

- (NSString *)errorDescription;

@end
