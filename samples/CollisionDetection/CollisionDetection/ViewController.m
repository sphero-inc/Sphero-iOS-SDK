//
//  Copyright (c) 2012-2014 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>
#import "ViewController.h"
#import "ConfigurationViewController.h"

@interface ViewController()
{
	BOOL        driving;
}

@property (strong, nonatomic) RKConvenienceRobot* robot;

@end

@implementation ViewController

- (void)drive:(id)sender{
	if (driving) {
		[self setDriving:NO];
		[_robot sendCommand:[RKRollCommand commandWithStopAtHeading:0.0]];
		[self resetSpeed];
		[self.driveButton setTitle:@"Go" forState:UIControlStateNormal];
	} else {
		[self setDriving:YES];
		[_robot sendCommand:[RKRollCommand commandWithHeading:self.controlHeadingSlider.value andVelocity:self.controlSpeedSlider.value ]];
		[self.driveButton setTitle:@"Stop" forState:UIControlStateNormal];
	}
}


- (void)calibrate:(id)sender{
	if (!aiming) {
		[self resetSpeed];
		[self setAiming:YES];
		[_robot sendCommand:[RKBackLEDOutputCommand commandWithBrightness:1.0]];
	} else {
		[self setAiming:NO];
		[_robot sendCommand:[RKBackLEDOutputCommand commandWithBrightness:0.0]];
		[_robot sendCommand:[RKSetHeadingCommand command]];
	}
	[self resetHeading];
}

- (void)configureDetection:(id)sender
{
	if (driving) {
		[_robot stop];
		[self setDriving:NO];
	} else if (aiming) {
		[self setAiming:NO];
		[_robot setBackLEDBrightness:0.0];
	}
	[_robot disableCollisions];
	[self presentConfigurationView];
}

- (void)speedValueChanged:(UISlider *)sender
{
	float speed = sender.value;
	if (driving) {
		[_robot driveWithHeading:self.controlHeadingSlider.value andVelocity:speed];
	}
	self.controlSpeedLabel.text = [NSString stringWithFormat:@"%.3f", speed];
}

- (void)headingValueChanged:(UISlider *)sender{
	float heading = sender.value;
	if (driving) {
		[_robot driveWithHeading:heading andVelocity:self.controlSpeedSlider.value];
	} else if (aiming) {
		[_robot driveWithHeading:heading andVelocity:0.0];
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

- (void)viewDidLoad{
	[super viewDidLoad];
	
	[self.view addSubview:self.unconnectedView];
	[self.view bringSubviewToFront:self.unconnectedView];
	
	aiming = NO;
	driving = NO;
}

-(void) viewDidAppear:(BOOL)animated{
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(robotChangedState:)];
	[RKRobotDiscoveryAgent startDiscovery];
}



-(void) robotChangedState:(RKRobotChangedStateNotification*) n{
	[self.unconnectedView removeFromSuperview];
	self.view.userInteractionEnabled = YES;
	[self presentConfigurationView];
	
}


- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData{
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

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation{
	return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


@end
