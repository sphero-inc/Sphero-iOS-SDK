//
//  ViewController.h
//  RobotUISample
//
//  Created by Jon Carroll on 12/9/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import <RobotKit/RobotKit.h>
#import "CircularUIView.h"

@interface ViewController : UIViewController <RUIColorPickerDelegate> {
    BOOL robotOnline;
    RUICalibrateGestureHandler *calibrateHandler;
    
    //Views that make up the drive joystick
    IBOutlet UIView *driveWheel;
    IBOutlet UIImageView *drivePuck;
    IBOutlet CircularUIView *circularView;
    BOOL ballMoving;
}

-(void)setupRobotConnection;
-(void)handleRobotOnline;

//Joystick drive related methods
-(float)clampWithValue:(float)value min:(float)min max:(float)max;
-(void)updateMotionIndicator:(RKDriveAlgorithm*)driveAlgorithm;
-(void)handleJoystickMotion:(id)sender;


//UI Interaction
-(IBAction)colorPressed:(id)sender;
-(IBAction)sleepPressed:(id)sender;


@end

