//
//  RKSensorControl.h
//  RobotKit
//
//  Created by Hunter Lang on 12/1/14.
//  Copyright (c) 2014 orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <RobotCommandKit/RobotCommandKit.h>

@class RKConvenienceRobot;

typedef NS_ENUM(int, RKStreamingRate) {
    RKDataStreamingRate1 = 1,
    RKDataStreamingRate10 = 10,
    RKDataStreamingRate20 = 20,
    RKDataStreamingRate50 = 50,
    RKDataStreamingRate100 = 100,
    RKDataStreamingRate200 = 200,
    RKDataStreamingRate400 = 400
};

@interface RKSensorControl : NSObject

@property (strong, nonatomic) RKConvenienceRobot *robot;

-(instancetype)sensorControlWithConvenienceRobot:(RKConvenienceRobot *)robot;
-(instancetype)initWithConvenienceRobot:(RKConvenienceRobot *)robot;

/*! Sphero robots contain powerful analysis functions to filter accelerometer data in order to detect collisions. Because this is a great example of a high-level concept that humans excel and – but robots do not – a number of parameters control the behavior. When a collision is detected an asynchronous message is generated. */
-(void) enableCollisions:(BOOL)enable;

/*! Sphero Robots provide real-time location data in the form of (X,Y) coordinates on the ground plane through the streaming interface. Note that the location will be inaccurate if the robot slips or drifts while navigating.  When a Robot wakes up it has coordinates (0,0) and heading 0, which corresponds to facing down the positive Y-axis with the positive X-axis to your right. This command allows you to move Sphero to a new location and change the alignment of locator coordinates with IMU headings. */
-(void) enableLocator:(BOOL)enable;

/*! Sphero supports asynchronous data streaming of important information from the sensors, IMU, and control system. The Set Data Streaming command determines what information Sphero will report, how often that information will be sampled, */
-(void) enableSensors:(RKDataStreamingMask)mask atStreamingRate:(RKStreamingRate)hz;

/*! */
-(void) disableSensors;

@end
