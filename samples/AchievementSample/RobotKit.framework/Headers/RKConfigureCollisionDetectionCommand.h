//
//  RKConfigureCollisionDetectionCommand.h
//  RobotKit
//
//  Created by Brian Smith on 2/23/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKDeviceCommand.h"

enum RKCollisionDetectionMethod {
    RKCollisionDetectionMethodDetectionOff  = 0,
    RKCollisionDetectionMethod1             = 1
};
typedef enum RKCollisionDetectionMethod RKCollisionDetectionMethod;


@interface RKConfigureCollisionDetectionCommand : RKDeviceCommand {
    RKCollisionDetectionMethod  method;
    uint8_t                     xThreshold;
    uint8_t                     yThreshold;
    uint8_t                     xSpeedThreshold;
    uint8_t                     ySpeedThreshold;
    NSTimeInterval              postTimeDeadZone;
}

@property (nonatomic, readonly) RKCollisionDetectionMethod  method;
@property (nonatomic, readonly) uint8_t                     xThreshold;
@property (nonatomic, readonly) uint8_t                     yThreshold;
@property (nonatomic, readonly) uint8_t                     xSpeedThreshold;
@property (nonatomic, readonly) uint8_t                     ySpeedThreshold;
@property (nonatomic, readonly) NSTimeInterval              postTimeDeadZone;

+ (void)sendCommandForMethod:(RKCollisionDetectionMethod)method 
                  xThreshold:(uint8_t)theXThreshold
                  yThreshold:(uint8_t)theYThreshold 
             xSpeedThreshold:(uint8_t)theXSpeedThreshold
             ySpeedThreshold:(uint8_t)theYSpeedThreshold
            postTimeDeadZone:(NSTimeInterval)deadZone;

+ (void)sendCommandToStopDetection;

- (id)initForMethod:(RKCollisionDetectionMethod)method 
         xThreshold:(uint8_t)theXThreshold
         yThreshold:(uint8_t)theYThreshold 
    xSpeedThreshold:(uint8_t)theXSpeedThreshold
    ySpeedThreshold:(uint8_t)theYSpeedThreshold
   postTimeDeadZone:(NSTimeInterval)deadZone;

@end
