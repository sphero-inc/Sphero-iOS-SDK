//
//  RKCollisionDetectedAsyncData.h
//  RobotKit
//
//  Created by Brian Smith on 2/23/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKDeviceAsyncData.h"

struct RKCollisionAcceleration {
    float x;
    float y;
    float z;
};
typedef struct RKCollisionAcceleration RKCollisionAcceleration;

struct RKCollisionAxis {
    bool x : 1;
    bool y : 1;
};
typedef struct RKCollisionAxis RKCollisionAxis;

struct RKCollisionPower {
    int x;
    int y;
};
typedef struct RKCollisionPower RKCollisionPower;


@interface RKCollisionDetectedAsyncData : RKDeviceAsyncData {
    @private
    RKCollisionAcceleration impactAcceleration;
    RKCollisionAxis         impactAxis;
    RKCollisionPower        impactPower;
    float                   impactSpeed;
    NSTimeInterval          impactTimeStamp;
}

@property (nonatomic, readonly) RKCollisionAcceleration impactAcceleration;
@property (nonatomic, readonly) RKCollisionAxis         impactAxis;
@property (nonatomic, readonly) RKCollisionPower        impactPower;
@property (nonatomic, readonly) float                   impactSpeed;
@property (nonatomic, readonly) NSTimeInterval          impactTimeStamp;

@end
