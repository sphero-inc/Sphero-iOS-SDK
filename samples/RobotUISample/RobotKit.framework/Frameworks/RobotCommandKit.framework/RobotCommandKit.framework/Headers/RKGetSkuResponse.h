//
//  RKGetSkuResponse.h
//  RobotCommandKit
//
//  Created by wes on 2/5/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKGetSkuResponse : RKDeviceResponse

@property (strong, readonly) NSString* sku;

-(BOOL) isDarkside;

@end
