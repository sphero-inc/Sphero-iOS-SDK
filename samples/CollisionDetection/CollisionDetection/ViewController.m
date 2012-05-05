//
//  ViewController.m
//  CollisionDetection
//
//  Created by Brian Smith on 2/23/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>

#import "ViewController.h"
#import "ConfigurationViewController.h"


@implementation ViewController

@synthesize unconnectedView;

// collision UI
@synthesize xAccelerationLabel;
@synthesize yAccelerationLabel;
@synthesize zAccelerationLabel;
@synthesize xAxisLabel;
@synthesize yAxisLabel;
@synthesize xPowerLabel;
@synthesize yPowerLabel;
@synthesize speedLabel;
@synthesize timeStampLabel;
@synthesize driveButton;
@synthesize aimButton;
@synthesize controlSpeedSlider;
@synthesize controlHeadingSlider;
@synthesize controlSpeedLabel;
@synthesize controlHeadingLabel;


// test drive control UI
@synthesize driveSpeedLabel;
@synthesize driveHeadingLabel;


- (void)drive:(id)sender
{
    if (driving) {
        [self setDriving:NO];
        [RKRollCommand sendStop];
        [self resetSpeed];
        [self.driveButton setTitle:@"Go" forState:UIControlStateNormal];
    } else {
        [self setDriving:YES];
        [RKRollCommand sendCommandWithHeading:self.controlHeadingSlider.value
                                     velocity:self.controlSpeedSlider.value];
        [self.driveButton setTitle:@"Stop" forState:UIControlStateNormal];
    }
}

- (void)calibrate:(id)sender
{
    if (!aiming) {
        [self resetSpeed];
        [self setAiming:YES];
        [RKBackLEDOutputCommand sendCommandWithBrightness:1.0];
    } else {
        [self setAiming:NO];
        [RKBackLEDOutputCommand sendCommandWithBrightness:0.0];
        [RKCalibrateCommand sendCommandWithHeading:0.0];
    }
    [self resetHeading];
}

- (void)configureDetection:(id)sender
{
    if (driving) {
        [RKRollCommand sendStop];
        [self setDriving:NO];
    } else if (aiming) {
        [self setAiming:NO];
        [RKBackLEDOutputCommand sendCommandWithBrightness:0.0];
    }
    [RKConfigureCollisionDetectionCommand sendCommandToStopDetection];
    [self presentConfigurationView];
}

- (void)speedValueChanged:(UISlider *)sender
{
    float speed = sender.value;
    if (driving) {
        [RKRollCommand sendCommandWithHeading:self.controlHeadingSlider.value
                                     velocity:speed];
    }
    self.controlSpeedLabel.text = [NSString stringWithFormat:@"%.3f", speed];
}

- (void)headingValueChanged:(UISlider *)sender
{
    float heading = sender.value;
    if (driving) {
        [RKRollCommand sendCommandWithHeading:heading
                                     velocity:self.controlSpeedSlider.value];
    } else if (aiming) {
        [RKRollCommand sendCommandWithHeading:heading velocity:0.0];
    }
    self.controlHeadingLabel.text = [NSString stringWithFormat:@"%.0f°", heading];
}

- (void)presentConfigurationView
{
    ConfigurationViewController *viewController = 
        [[ConfigurationViewController alloc] initWithNibName:nil bundle:nil];
    
    [self presentModalViewController:viewController animated:YES];
}

- (void)setDriving:(BOOL)state
{
    if (state) {
        driving = YES;
        self.aimButton.enabled = NO;
    } else {
        driving = NO;
        self.aimButton.enabled = YES;
    }
}

- (void)setAiming:(BOOL)state
{
    if (state) {
        aiming = YES;
        self.driveButton.enabled = NO;
        self.controlSpeedSlider.enabled = NO;
    } else {
        aiming = NO;
        self.driveButton.enabled = YES;
        self.controlSpeedSlider.enabled = YES;
    }
}

- (void)resetHeading
{
    self.controlHeadingLabel.text = @"0°";
    self.controlHeadingSlider.value = 0.0;
}

- (void)resetSpeed
{
    self.controlSpeedLabel.text = @"0.0";
    self.controlSpeedSlider.value = 0.0;
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(handleApplicationDidBecomeActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleApplicationWillResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    
    [self.view addSubview:self.unconnectedView];
    [self.view bringSubviewToFront:self.unconnectedView];
    
    aiming = NO;
    driving = NO;
}

- (void)handleApplicationDidBecomeActive:(NSNotification *)notification
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleRobotOnline:)
                                                 name:RKDeviceConnectionOnlineNotification
                                               object:nil];
    [[RKRobotProvider sharedRobotProvider] openRobotConnection];
}

- (void)handleApplicationWillResignActive:(NSNotification *)notification
{
    [RKConfigureCollisionDetectionCommand sendCommandToStopDetection];
    [[RKDeviceMessenger sharedMessenger] removeDataStreamingObserver:self]; 
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

- (void)handleRobotOnline:(NSNotification *)notification
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:RKDeviceConnectionOnlineNotification
                                                  object:nil];
    // observe async data
    [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self
                                                         selector:@selector(handleAsyncData:)];
    
    [self.unconnectedView removeFromSuperview];
    self.view.userInteractionEnabled = YES;
    [self presentConfigurationView];
}

- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
{
    if ([asyncData isKindOfClass:[RKCollisionDetectedAsyncData class]]) {
        RKCollisionDetectedAsyncData *collisionData = (RKCollisionDetectedAsyncData *)asyncData;
        self.xAccelerationLabel.text = [NSString stringWithFormat:@"%.4f", 
                                        collisionData.impactAcceleration.x];
        self.yAccelerationLabel.text = [NSString stringWithFormat:@"%.4f",
                                        collisionData.impactAcceleration.y];
        self.zAccelerationLabel.text = [NSString stringWithFormat:@"%.4f",
                                        collisionData.impactAcceleration.z];
        self.xAxisLabel.text = collisionData.impactAxis.x ? @"☑" : @"☒";
        self.yAxisLabel.text = collisionData.impactAxis.y ? @"☑" : @"☒";
        self.xPowerLabel.text = [NSString stringWithFormat:@"%i",
                                 collisionData.impactPower.x];
        self.yPowerLabel.text = [NSString stringWithFormat:@"%i",
                                 collisionData.impactPower.y];
        self.speedLabel.text = [NSString stringWithFormat:@"%.3f",
                                collisionData.impactSpeed];
        self.timeStampLabel.text = [NSString stringWithFormat:@"%.3f",
                                collisionData.impactTimeStamp];
    }
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
