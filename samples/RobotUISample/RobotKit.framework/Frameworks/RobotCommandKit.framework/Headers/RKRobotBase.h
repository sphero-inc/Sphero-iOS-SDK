//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRobotBase.h"
#import "RKDeviceCommand.h"
#import "RKDeviceResponse.h"
#import "RKDeviceAsyncData.h"
#import "RKVersioningResponse.h"
#import "RKGoToSleepCommand.h"

typedef void (^RKDeviceResponseBlock)(RKDeviceResponse* response);

@protocol RKResponseObserver; // fwd declaration


/*! The basis for any connected device that sends commands and receives responses & broadcasts */
@protocol RKRobotBase <NSObject>

/*! unique identifier - btAddress for Classic and NSUUID for BLE */
-(NSString*) identifier;
-(NSString*) serialNumber;
-(NSString*) name;

-(void) streamCommand:(RKDeviceCommand*) command;
-(void) sendCommand:(RKDeviceCommand *)command;

-(void) addResponseObserver:(__weak id<RKResponseObserver>) observer;
-(void) removeResponseObserver:(id<RKResponseObserver>) observer;

-(NSNumber*) connectTimeInSeconds;
-(RKVersioningResponse*) versions;

/*! Robot radio is connected but there is no guarantee of the Main Firmware App state. */
-(BOOL) isConnected;

/*! Robot is Online, in the Main Firmware App and is ready for play! */
-(BOOL) isOnline;

-(BOOL) isBootloader;

/*! default sleep mode for a robot.  BTLE robots sleep is different from Classic Robots. */
-(void) sleep;
-(void) sleep:(RKSleepType)type;


/*! request this robot disconnect */
-(void) disconnect;

@end


/*! responses and unsolicited broadcast messages from the robot */
@protocol RKResponseObserver <NSObject>

@optional

-(void) handleResponse:(RKDeviceResponse*) response forRobot:(id<RKRobotBase>) robot;
-(void) handleResponseString:(NSString*) stringResponse forRobot:(id<RKRobotBase>) robot;
-(void) handleAsyncMessage:(RKAsyncMessage*) message forRobot:(id<RKRobotBase>) robot;


//#pragma mark - responses
//-(void) handleReadOdometerResponse:(RKGetOdometerResponse*) response forRobot:(id<RKRobotBase>) robot;
//
//
//#pragma mark - unsolicted robot messages
//
//-(void) handleSleepWillOccurAsyncMessage:(RKSleepWillOccurMessage*) msg forRobot:(id<RKRobotBase>) robot;
//-(void) handleSleepDidOccurAsyncMessage:(RKSleepDidOccurMessage*) msg forRobot:(id<RKRobotBase>) robot;
//-(void) handleCollisionDetectedAsyncMessage:(RKCollisionDetectedAsyncData*) msg forRobot:(id<RKRobotBase>) robot;
//-(void) handleSensorsAsyncData:(RKDeviceSensorsAsyncData*) msg forRobot:(id<RKRobotBase>) robot;
//[self registerClass:[RKSelfLevelCompleteAsyncData class]];
//[self registerClass:[RKPowerNotificationAsyncData class]];

@end
