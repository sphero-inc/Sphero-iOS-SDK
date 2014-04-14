//
//  RKAccuAngleFilter.h
//  RobotKit
//
//  Created by wes felteau on 3/25/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RKDriveAlgorithm.h"

@interface RKAccuAngleDriveAddon : NSObject <RKDriveVectorAddon>

@property ( readwrite ) BOOL enabled;
@property ( readwrite ) int32_t rotationRateThreshold;
@property ( readwrite ) float_t outputRatio;
@end
