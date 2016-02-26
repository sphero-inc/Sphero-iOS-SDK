//
//  RKReadOdometerResponse.h
//  RobotCommandKit
//
//  Created by wes on 6/30/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import "RobotCommandKit.h"

@interface RKReadOdometerResponse : RKDeviceResponse

@property (readonly) uint32_t distanceInCentimeters;

@end
