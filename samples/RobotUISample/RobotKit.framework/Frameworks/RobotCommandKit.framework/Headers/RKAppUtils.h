//
//  RKAppUtils.h
//  RobotCommandKit
//
//  Created by wes on 5/11/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@interface RKAppUtils : NSObject

+ (BOOL)isAppActive;
+ (BOOL)isAppForeground;

@end
