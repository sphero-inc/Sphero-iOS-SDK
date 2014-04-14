//
//  RUICalibrationViewController.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RUIModalLayerViewController.h>
#import <RobotUIKit/RUICalibrationView.h>

@protocol RKRobotControlProtocol;

/*!
 * @brief Modal view controller that allows the user to calibrate the Sphero
 *        heading.
 *
 * This view controller puts the robot into calibration mode and presents the user
 * with a wheel that they can use to rotate the Sphero without moving it.  The
 * new heading is used to orient the Sphero's orientation relative to that of the
 * controllers.
 */
@interface RUICalibrationViewController : 
	RUIModalLayerViewController <RUICalibrationViewDelegate> {
	@private
        RUICalibrationView *calibrationView;
        id<RKRobotControlProtocol> robotControl;
		IBOutlet UILabel		*calibrationLabel;
		IBOutlet UIButton		*rollButton;
        IBOutlet UILabel        *rollLabel;
}

/*! The calibration view used to rotate the Sphero. */
@property (nonatomic, retain) IBOutlet RUICalibrationView*  calibrationView;

/*! The robot control that is used to communicate with the robot. */
@property (nonatomic, assign) id<RKRobotControlProtocol>    robotControl;

/*! The action to be executed when the user has finished calibrating the robot. */
- (IBAction)done;

-(void)layoutPortrait;
-(void)layoutLandscape;

@end