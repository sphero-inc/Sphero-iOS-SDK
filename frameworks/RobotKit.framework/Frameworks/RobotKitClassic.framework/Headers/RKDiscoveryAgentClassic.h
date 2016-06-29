//
//  Copyright 2013 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <ExternalAccessory/ExternalAccessory.h>
#import <RobotCommandKit/RobotCommandKit.h>

@class RKRobotClassic;

/*!
 *  @brief Find and Connect to Orbotix Classic Robots Sphero v1/v2.
 */
@interface RKDiscoveryAgentClassic : NSObject <RKDiscoveryAgent, EAAccessoryDelegate>

/*! Available robots. - NOT NECESSARILY CONNECTED */
@property ( nonatomic, readonly , strong) NSMutableOrderedSet *availableRobots;

-(NSOrderedSet*) connectedRobots;

/*! 
 *  Sets the connection to skip jumping to the main application when opening
 *  the connection.
 */
@property ( nonatomic, assign ) BOOL startInBootloader;
/*!
 *  Returns the shared Classic (Sphero 1.0 & 2.0) Discovery Agent object that manages a connected robot.
 *  @return The shared robot provider object.
 */
+ (RKDiscoveryAgentClassic *) sharedAgent;

-(BOOL) startDiscovery;

-(void) stopDiscovery;

-(void) connect:(RKRobotClassic*) robot;

-(void) connect:(RKRobotClassic*) robot withCompletionHandler:(RKRobotConnectBlock) connectBlock;

-(void) disconnect:(RKRobotClassic*) robot;

-(void) disconnectAll;

-(NSOrderedSet*) onlineRobots;

- (BOOL) isDiscovering;

-(void) setShouldAutoConnect:(BOOL) shouldAutoConnect;

@end


#pragma mark -
#pragma mark Notification String Constants
/*!
 * Notification string which is used post an NSNotification when a Robot is about to
 * go to sleep. The userInfo dictionary contains the RKRobot object that is going to sleep.
 */
//extern NSString *const RKRobotWillGoToSleepNotification;
