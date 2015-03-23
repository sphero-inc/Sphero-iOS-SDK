//
//  AppDelegate.m
//  HelloWorld_OSX
//
//  Created by wes on 11/21/14.
//  Copyright (c) 2014 Sphero. All rights reserved.
//

#import "AppDelegate.h"
#import <RobotKit_OSX/RobotKit.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
	// Insert code here to tear down your application
	[RKRobotDiscoveryAgentLE stopDiscovery];
	[[RKRobotDiscoveryAgentLE sharedAgent] disconnectAll];
}

- (void)applicationDidBecomeActive:(NSNotification *)notification {
    
}

- (void)applicationWillResignActive:(NSNotification *)notification {
    
}

@end
