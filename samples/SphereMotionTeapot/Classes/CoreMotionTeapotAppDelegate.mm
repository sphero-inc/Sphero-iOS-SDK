/*
    File: CoreMotionTeapotAppDelegate.m
Abstract: CoreMotionTeapot's app delegate.
 Version: 1.0

*/

#import <CoreMotion/CoreMotion.h>
#import "CoreMotionTeapotAppDelegate.h"
#import "EAGLView.h"
#import <RobotKit/RobotKit.h>

@implementation CoreMotionTeapotAppDelegate

@synthesize window;
@synthesize glView;

- (void) applicationDidFinishLaunching:(UIApplication *)application
{
    //Set the streaming default values
    NSMutableDictionary *defaults = [[NSMutableDictionary alloc] init];
    [defaults setObject:@"20" forKey:@"rateDivisor"];
    [defaults setObject:@"1" forKey:@"framesPacket"];
    [defaults setObject:@"0" forKey:@"packetCount"];
    [[NSUserDefaults standardUserDefaults] registerDefaults:defaults];
    
	[glView startAnimation];
}

- (void) applicationWillResignActive:(UIApplication *)application
{
    //Turn stabilization back on and close the connection if the app is closing or going into the background
	[glView stopAnimation];
    [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOn];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    //Turn stabilization back on and close the connection if the app is closing or going into the background
	[glView stopAnimation];
    [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOn];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    //Turn stabilization back on and close the connection if the app is closing or going into the background
    [glView stopAnimation];
    [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOn];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Watch for online notification to start driving
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleConnectionOnline:) name:RKDeviceConnectionOnlineNotification object:nil];
    
    // Try to bring the robot online and display an alert if there isn't a robot
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    } else {
        UIAlertView *no_robot_alert = [[UIAlertView alloc] initWithTitle:@"No Sphero" message:@"Go to the Settings app to connect." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles: nil];
        [no_robot_alert show];
        [no_robot_alert release];
    }
    
    [glView startAnimation];
}


-(void)handleConnectionOnline:(NSNotification*)notification {
    NSLog(@"Online Notification");
    
    //Make Sphero yellow
    [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:1.0 blue:0.0];
    //Turn off stabilization so Sphero doesn't try to right himself
    [RKStabilizationCommand sendCommandWithState:RKStabilizationStateOff];
    
    [glView performSelector:@selector(enableSpheroStreaming) withObject:nil afterDelay:0.1];
}

- (void) dealloc
{
	[window release];
	[glView release];
	
	[super dealloc];
}

@end
