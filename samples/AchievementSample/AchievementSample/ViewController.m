//
//  ViewController.m
//  AchievementSample
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"

#import "RobotKit/RobotKit.h"

#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController

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
    
    //Register to be notified when an achievement is earned.
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(spheroWorldAchievementEarned:) name:RKAchievementEarnedNotification object:nil];

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;

    calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
}

- (void)viewDidUnload
{
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
    return UIInterfaceOrientationIsPortrait(interfaceOrientation);
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

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    robotOnline = YES;
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    }
}

#pragma mark -
#pragma mark Interface actions

-(IBAction)redPressed:(id)sender {
    //Record that red was pressed so it is counted toward achievement progress
    [RKAchievement recordEvent:@"red"];
    //Change Sphero's color to red
    [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:0.0 blue:0.0];
}

-(IBAction)greenPressed:(id)sender {
    //Record that green was pressed so it is counted toward achievement progress
    [RKAchievement recordEvent:@"green" withCount:1];
    //Change Sphero's color to green
    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:1.0 blue:0.0];
}

-(IBAction)bluePressed:(id)sender {
    //Record that blue was pressed so it is counted toward achievement progress
    [RKAchievement recordEvent:@"blue"];
    //Change Sphero's color to blue
    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:1.0];
}

-(IBAction)spheroWorldPressed:(id)sender {
    //Display the SpheroWorld authorization view, it will display the user's achievements if already logged in
    RKSpheroWorldAuth *spheroWorld = [[RKSpheroWorldAuth alloc] init];
    spheroWorld.delegate = self;
    [self presentModalViewController:spheroWorld animated:YES];
    [spheroWorld release];
}

#pragma mark -
#pragma mark Achievement related

-(void)spheroWorldAchievementEarned:(NSNotification*)notification {
    //Get the achievement that was earned from the userInfo dictionary
    RKAchievement *achievement = [notification.userInfo objectForKey:RKAchievementEarnedAchievementKey];
    
    //This would be the appropriate time to play a sound a let the user know they earned an achievment
    //RobotUIKit has a view made for doing this, we are going to show how to use it
    
    //RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
    NSString* rootpath = [[NSBundle mainBundle] bundlePath];
    NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
    NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
    
    RUIAchievementEarnedViewController *controller = [[RUIAchievementEarnedViewController alloc] initWithNibName:@"RUIAchievementEarnedViewController" bundle:ruiBundle];
    [controller setAchievement:achievement];
    [controller displayInView:self.view];
    [controller release];
    //This will automatically animate itself off screen after 5 second and release any resources.
}

- (void)dealloc {
    [super dealloc];
}

@end
