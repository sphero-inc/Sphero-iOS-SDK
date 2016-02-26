//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKOvalDeviceBroadcast : RKAsyncMessage

@property (strong, nonatomic) NSArray* floats;
@property (nonatomic, strong) NSArray *ints;

- (NSString *)stringInterpretation;

@end
