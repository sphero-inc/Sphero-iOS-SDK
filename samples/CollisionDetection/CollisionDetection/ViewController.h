//
//  ViewController.h
//  CollisionDetection
//
//  Created by Brian Smith on 2/23/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKit/RobotKit.h>

@class RKDeviceAsyncData;

@interface ViewController : UIViewController <RKResponseObserver> {
		BOOL        aiming;
}


@property (nonatomic, retain) IBOutlet UIView       *unconnectedView;

// collision UI
@property (nonatomic, retain) IBOutlet UILabel      *xAccelerationLabel;
@property (nonatomic, retain) IBOutlet UILabel      *yAccelerationLabel;
@property (nonatomic, retain) IBOutlet UILabel      *zAccelerationLabel;
@property (nonatomic, retain) IBOutlet UILabel      *xAxisLabel;
@property (nonatomic, retain) IBOutlet UILabel      *yAxisLabel;
@property (nonatomic, retain) IBOutlet UILabel      *xPowerLabel;
@property (nonatomic, retain) IBOutlet UILabel      *yPowerLabel;
@property (nonatomic, retain) IBOutlet UILabel      *speedLabel;
@property (nonatomic, retain) IBOutlet UILabel      *timeStampLabel;
@property (nonatomic, retain) IBOutlet UIButton     *driveButton;
@property (nonatomic, retain) IBOutlet UIButton     *aimButton;
@property (nonatomic, retain) IBOutlet UISlider     *controlSpeedSlider;
@property (nonatomic, retain) IBOutlet UISlider     *controlHeadingSlider;
@property (nonatomic, retain) IBOutlet UILabel      *controlSpeedLabel;
@property (nonatomic, retain) IBOutlet UILabel      *controlHeadingLabel;

// test drive control UI
@property (nonatomic, retain) IBOutlet UILabel      *driveSpeedLabel;
@property (nonatomic, retain) IBOutlet UILabel      *driveHeadingLabel;

- (IBAction)drive:(id)sender;
- (IBAction)calibrate:(id)sender;
- (IBAction)configureDetection:(id)sender;
- (IBAction)speedValueChanged:(id)sender;
- (IBAction)headingValueChanged:(id)sender;

- (void)presentConfigurationView;

- (void)setDriving:(BOOL)state;
- (void)setAiming:(BOOL)state;
- (void)resetHeading;
- (void)resetSpeed;

- (void)handleApplicationDidBecomeActive:(NSNotification *)notification;
- (void)handleApplicationWillResignActive:(NSNotification *)notification;
- (void)handleRobotOnline:(NSNotification *)notification;
- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData;

@end
