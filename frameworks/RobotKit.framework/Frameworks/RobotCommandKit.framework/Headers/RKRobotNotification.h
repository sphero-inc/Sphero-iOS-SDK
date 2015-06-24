//
//  Copyright (c) 2014 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRobotBase.h"

extern NSString * const kRobotDidChangeStateNotification;
extern NSString * const kRobotIsAvailableNotification;
extern NSString * const kRobotRemoteRSSIChangedNotification;

extern NSString* const kDiscoveryScanDidStart;
extern NSString* const kDiscoveryScanDidStop;

/*! Base Robot Notification - contains the robot in userInfo with accessor*/
@interface RKRobotNotification : NSNotification

-(id) initWithRobot:(id<RKRobotBase>) robot;

@property (strong, nonatomic) id<RKRobotBase> robot;

@end


// the enum values in RKNodeStateChangeNotificationType must match - this is the master list
typedef NS_ENUM(uint8_t, RKRobotChangedStateNotificationType) {
	/*! Robot connection process has started */
   	RKRobotConnecting = 10,
	
	/*! Robot is connected, but not online */
	RKRobotConnected = 20,
	
	/*! Robot main processor is online and connected - This state is the one to watch for before sending commands */
	RKRobotOnline = 30,
	
	/*! Robot main process is offline, but the radio is still connected.  (Only available in BLE Robots) */
   	RKRobotOffline = 40,
	
	/*! Robot radio has disconnected - does not imply that that robot main processor is offline */
	RKRobotDisconnected = 50,
	
	/*! Something went wrong during the connect cycle. */
   	RKRobotFailedConnect = 90
};

/*! Used to notify that a Robot is within range and connectable. */
@interface RKRobotAvailableNotification : RKRobotNotification

@property (strong,nonatomic) NSArray* robots;

+(id) notificationWithRobot:(id<RKRobotBase>)robot andRobots:(NSArray*) robots;

@end



/*! Base Robot Changed State Notification - Fire when the robot is connecting, connected, online, etc.
 Please check the state for the main processor to assess Bootloader or MainApp. */
@interface RKRobotChangedStateNotification : RKRobotNotification

@property (readonly) RKRobotChangedStateNotificationType type;

+(id) notificationWithRobot:(id<RKRobotBase>) robot andType:(RKRobotChangedStateNotificationType) type;

-(NSString*) typeString;

@end



@interface RKRobotRSSIChangedNotification : RKRobotNotification

+(id) notificationWithRobot:(id<RKRobotBase>) robot andRemoteRSSI:(uint8_t) rssi;

@property (readonly) int8_t remoteRSSI;

- (NSNumber *)signalQuality;

@end
