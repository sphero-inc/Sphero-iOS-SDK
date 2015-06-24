//
//  RUICalibrationViewController.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RUIModalViewController.h>
#import <RobotUIKit/RUICalibrationView.h>
#import <RobotKit/RobotKit.h>


/*!
 * @brief Modal view controller that allows the user to calibrate the Sphero
 *        heading.
 *
 * This view controller puts the robot into calibration mode and presents the user
 * with a wheel that they can use to rotate the Sphero without moving it.  The
 * new heading is used to orient the Sphero's orientation relative to that of the
 * controllers.
 */
@interface RUICalibrationViewController : RUIModalViewController <RUICalibrationViewDelegate> {
	@private
      IBOutlet UILabel	 *calibrationLabel;
      IBOutlet UIButton	 *rollButton;
      IBOutlet UILabel   *rollLabel;
}

@property (nonatomic, strong) id<RKRobotBase> robot;

/*! The calibration view used to rotate the Sphero. */
@property (nonatomic, strong) IBOutlet RUICalibrationView*  calibrationView;

/*! The action to be executed when the user has finished calibrating the robot. */
- (IBAction)done;

-(void)layoutPortrait;
-(void)layoutLandscape;

@end