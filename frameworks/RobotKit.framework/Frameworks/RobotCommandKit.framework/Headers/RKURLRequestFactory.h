//
//  RKWebAsyncRequestFactory.h
//  RobotKitLE
//
//  Created by Hunter Lang on 7/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RKURLRequestFactory : NSObject

+ (NSURLRequest *)requestWithURL:(NSURL *)URL stats:(NSArray *)stats;

@end
