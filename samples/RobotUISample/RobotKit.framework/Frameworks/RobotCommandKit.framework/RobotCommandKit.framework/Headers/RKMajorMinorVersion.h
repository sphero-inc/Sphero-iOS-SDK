//
//  RKMajorMinorVersion.h
//  RobotCommandKit
//
//  Created by wes on 5/4/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RKMajorMinorVersion : NSObject

@property (nonatomic, strong, readonly) NSString* major;
@property (nonatomic, strong, readonly) NSString* minor;

+(id) versionWithString:(NSString*) versionString;

-(NSComparisonResult) compare:(RKMajorMinorVersion*) version;

-(bool) isGreaterThan:(RKMajorMinorVersion*) version;

-(bool) isLessThan:(RKMajorMinorVersion*) version;

-(NSString*) versionString;

@end
