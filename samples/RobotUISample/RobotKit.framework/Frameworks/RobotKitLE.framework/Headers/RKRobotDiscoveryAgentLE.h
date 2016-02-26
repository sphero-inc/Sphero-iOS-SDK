#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import "RKRobotLE.h"
#import "RKLeConnectStrategy.h"
#import "RKDiscoveryAgentLE.h"
#import <RobotCommandKit/RobotCommandKit.h>


/*!
 @brief Discover & Connect to Bluetooth LE Robots
 Discovery and connection services for Robots
 Simple Connect
 @code
 [[RKRobotDiscoveryAgentLE sharedAgent]
 connect:robot
 withCompletionHandler:(RKRobotConnectBlock) connectBlock;
 
 @endcode
 
 Connect using @p RKRobotStateChangeNotification @c
 @code
 // setup notification listener
 [[NSNotificationCenter defaultCenter]
 addObserver:self
 selector:@selector(didChangeRobotStateNotification:)
 name:kRobotDidChangeStateNotification
 object:nil];
 [[RKRobotDiscoveryAgentLE sharedAgent] startDiscovery];
 @endcode
 
 
 @copyright (c) 2013-2014 Sphero.
 @author Wes Felteau
 */
@interface RKRobotDiscoveryAgentLE : NSProxy <RKDiscoveryAgent, RKDiscoveryAgentLE>

+(RKRobotDiscoveryAgentLE *) sharedAgent;

+(id<RKRobotBase>) robotForName:(NSString*) name;
-(id<RKRobotBase>) robotForName:(NSString*) name;

- (NSOrderedSet*) connectingRobots;

/*! radio connected robots 
 @returns proxy to connectedNodes */
- (NSOrderedSet*) connectedRobots;

/*! online (main processor on) robots 
 @returns proxy to onlineNodes */
- (NSOrderedSet*) onlineRobots;

@end
