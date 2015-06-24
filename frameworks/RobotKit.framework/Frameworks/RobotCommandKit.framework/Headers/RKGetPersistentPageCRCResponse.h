//
//  RKGetPersistentPageCRCResponse.h
//  RobotCommandKit
//
//  Created by Corey Earwood on 4/28/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

@interface RKGetPersistentPageCRCResponse : RKDeviceResponse

- (BOOL)compareCRCWithData:(NSData *)data;

@end
