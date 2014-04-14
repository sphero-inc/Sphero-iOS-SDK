//
//  ViewController.m
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController
@synthesize connectionLabel;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
    noSpheroViewShowing = NO;
}

- (void)viewDidUnload
{
    [connectionLabel release];
    connectionLabel = nil;
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

-(void)appWillResignActive:(NSNotification*)notification {
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

#pragma mark- Sphero Connections

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    connectionLabel.text = @"CONNECTED";
    
    if(!robotOnline) {
        robotOnline = YES;
        /*Only start the blinking loop once*/
        [self toggleLED];
    }
    // Hide No Sphero Connected View
    if( noSpheroViewShowing ) {
        [noSpheroView dismissModalLayerViewControllerAnimated:YES];
        noSpheroViewShowing = NO;
    }
    robotOnline = YES;
}

-(void)setupRobotConnection {
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleDidGainControl:) name:RKRobotDidGainControlNotification object:nil];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOffline) name:RKDeviceConnectionOfflineNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOffline) name:RKRobotDidLossControlNotification object:nil];
    
    //Attempt to control the connected robot so we get the notification if one is connected
    
    robotInitialized = NO;
    robotOnline = NO;
    

    [[RKRobotProvider sharedRobotProvider] openRobotConnection];
    
    
    connectionLabel.text = @"CONNECTING";
    // Give the device a second to connect
    [self performSelector:@selector(showNoSpheroConnectedView) withObject:nil afterDelay:1.0];
    
    robotInitialized = YES;
}

-(void)handleDidGainControl:(NSNotification*)notification {\
    NSLog(@"didGainControlNotification");
    if(!robotInitialized) return;
    [[RKRobotProvider sharedRobotProvider] openRobotConnection];
}

- (void)handleRobotOffline {
    if(robotOnline) {
        robotOnline = NO;
        //Put code to update UI for offline here
        connectionLabel.text = @"DISCONNECTED";
        [self showNoSpheroConnectedView];
    }
}

- (void)toggleLED {
    /*Toggle the LED on and off*/
    if (ledON) {
        ledON = NO;
        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];
    } else {
        ledON = YES;
        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:1.0];
    }
    // Only continue funciton if we are connect to robot
    if( robotOnline ) [self performSelector:@selector(toggleLED) withObject:nil afterDelay:0.5];
}

-(void)showNoSpheroConnectedView {
    if( robotOnline ) return;
    //RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
    NSString* rootpath = [[NSBundle mainBundle] bundlePath];
    NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
    NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
    
    NSString* nibName;
    // Set up for iPhone/ipod
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        // Change if your app is portrait
        nibName = @"RUINoSpheroConnectedViewController_Portrait";
        //nibName = @"RUINoSpheroConnectedViewController_Landscape";
    }
    // Set up for iPad
    else {
        // Change if your app is portrait
        nibName = @"RUINoSpheroConnectedViewController_iPad_Portrait";
        // nibName = @"RUINoSpheroConnectedViewController_iPad_Landscape";
    }
        
    noSpheroView = [[RUINoSpheroConnectedViewController alloc]
                                                        initWithNibName:nibName
                                                        bundle:ruiBundle];
    [self presentModalLayerViewController:noSpheroView animated:YES];
    noSpheroViewShowing = YES;
}

- (void)dealloc {
    [noSpheroView release];
    [connectionLabel release];
    [super dealloc];
}
@end
