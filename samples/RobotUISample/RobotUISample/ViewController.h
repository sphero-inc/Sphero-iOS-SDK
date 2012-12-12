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

@interface ViewController : UIViewController <RUIColorPickerDelegate, RUICalibrateButtonGestureHandlerProtocol> {
    
    // Sphero state variables
    BOOL robotOnline;
    BOOL ballMoving;
    BOOL allowCalibrating;
    
    // Controls calibration gestures
    RUICalibrateButtonGestureHandler *calibrateAboveHandler;
    
    // Controls two finger calibration gestures
    RUICalibrateGestureHandler *calibrateTwoFingerHandler;
    
    //Views that make up the drive joystick
    IBOutlet UIView *driveWheel;
    IBOutlet UIImageView *drivePuck;
    IBOutlet CircularUIView *circularView;
    
    // Buttons from NIB that link to a calibration gesture handler
    IBOutlet UIButton *calibrateAboveButton;
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

