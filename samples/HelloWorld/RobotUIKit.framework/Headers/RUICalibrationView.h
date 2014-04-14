//
//  RUICalibrationView.h
//  RobotUIKit
//
//  Created by Brian Alexander on 5/24/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol RUICalibrationViewDelegate;

/*!
 * @brief View class showing a control wheel with a knob that the user can
 *        grab and rotate to point the robot in different directions.
 */
@interface RUICalibrationView : UIView {
	@private
	UIImageView*  controlKnobView;
	UIImageView*  wheelView;
	CGFloat       rotationRadius;
	CGPoint       wheelCenter;
	CGFloat       currentAngle;
	CGFloat       wheelBorderSize;
	BOOL          rotateView;
	id<RUICalibrationViewDelegate> delegate;
}

/*!
 * The target object that is notified whenever the user rotates the 
 * calibration wheel.
 */
@property (nonatomic, assign) id<RUICalibrationViewDelegate> delegate;

/*!
 * Get or set the wheel border size.  The wheel border keeps the calibration
 * knob a specific distance inside the calibration wheel.  A smaller value will
 * move the knob farther out in the wheel.
 */
@property (nonatomic, assign) CGFloat wheelBorderSize;

/*!
 * Get or set the control knob diameter.
 */
@property (nonatomic, assign) CGFloat controlKnobDiameter;

/*!
 * Set whether the control knob should be moved around the wheel or if the
 * wheel itself should be rotated to indicate the directional change.
 */
@property (nonatomic, assign) BOOL rotateView;

/*!
 * Set a new image for the calibration wheel.  If this is nil then the wheel
 * is not drawn.
 * 
 * @param image The new image for the calibration wheel.
 */
- (void)setWheelImage:(UIImage*)image;

/*!
 * Set a new image for the calibration knob that the user can grab and rotate.
 *
 * @param image The new image for the calibration knob.
 */
- (void)setKnobImage:(UIImage*)image;

/*!
 * Reset so the control knob is at the top of the view.
 */
- (void)reset;

@end

/*!
 * @brief Protocol for the calibration view delegate to implement.
 *
 * The delegate is notified whenever the rotation in the calibration view
 * changes.
 */
@protocol RUICalibrationViewDelegate <NSObject>

/*!
 * Called when the calibration view's heading changes.
 *
 * @param view The calibration view that changed
 * @param angle The new heading from the view, suitable for sending to the
 *              robot control in the rotateToHeading method.
 */
- (void)calibrationViewHeadingDidChange:(RUICalibrationView*)view
							  toHeading:(float)angle;

@optional
/*!
 * Called when the user has stopped moving the calibration knob.  The user may
 * move the knob again in which case this method will be called again.
 *
 * @param view The calibration view that changed.
 */
- (void)calibrationViewHeadingSet:(RUICalibrationView*)view;

@end
