//
//  RUICalibrateButtonGestureHandler.h
//  RobotUIKit
//
//  Created by Mike DePhillips on 10/23/12.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class RUICalibrateButtonGestureHandler;
@protocol RUICalibrateButtonGestureHandlerProtocol;

/*! Type that is used for setting the location of the circle respect to the button */
typedef int RUICalibrationCircleLocation;
// Don't change the values of the enum because RUICalibrateTouchOverlayView depends
// on these values to be the ones they are
enum {
    /*! Draws the calibration circle to the left of the button */
    RUICalibrationCircleLocationLeft   = 0,
    /*! Draws the calibration circle above the button */
    RUICalibrationCircleLocationAbove  = 1,
    /*! Draws the calibration circle to the right of the button */
    RUICalibrationCircleLocationRight  = 2,
    /*! Draws the calibration circle below the button */
    RUICalibrationCircleLocationBelow  = 3,
};

/*!
 *@brief Class to add a rotation gesture recognizer to a view and automatically display
 * the rotation rings on the furthest superview
 */
@interface RUICalibrateButtonGestureHandler : NSObject {
    id <RUICalibrateButtonGestureHandlerProtocol> delegate;
    @private
    UIView *view;
    UIGestureRecognizer *recognizer;
    CGPoint startPoint;
    int calibrationRadius;
    RUICalibrationCircleLocation calibrationCircleLocation;
    
    UIImage* backgroundImage;
    UIImage* foregroundImage;
    UIColor* backgroundColor;
    UIColor* foregroundColor;
    UIButton*  calibrateButton;
    BOOL isCalibrating;
}

/*!
 *  Size of the radius of the calibration circle in pixels
 */
@property (nonatomic, assign) int calibrationRadius;

/*!
 *  The variable that controls where the calibration circle is drawn with
 *  respect to the button that triggers calibration
 */
@property (nonatomic, assign) RUICalibrationCircleLocation calibrationCircleLocation;

/*!
 *  Delegate that will be notified when calibration begins and ends so sounds can be played
 */
@property (nonatomic, assign) id <RUICalibrateButtonGestureHandlerProtocol> delegate;

@property (nonatomic, retain) UIGestureRecognizer *recognizer;

/*!
 *  @param _view - the background view that you want the gesture recognizer to be added to
 *  @param button - the button that intiates the calibration gesture
 */
-(id)initWithView:(UIView*)_view button:(UIView*)button;

/*!
 *  @return YES if a calibration is currently in progress
 */
+(BOOL)isCalibrating;

/*!
 *  @return the gesture recognizer used by the handler if you need to require other recogniers to fail
 */
-(UIGestureRecognizer*)getGestureRecognizer;

/*!
 *  @return the currently overlay view if calibrating for customizing background color
 *  Will return nil if not currenlty calibrating
 */
-(UIView*)getOverlayView;

/*!
 * Callback when touchView has a touch down event
 */
-(void)startCalibration;

/*!
 * Callback when touch gesture is over or cancelled
 */
-(void)endCalibration;

/*! 
 * Set the background button image color 
 */
-(void)setForegroundWithColor:(UIColor*)color;

/*! 
 * Set the foreground button image color 
 */
-(void)setBackgroundWithColor:(UIColor*)color;

@end

/*!
 * Protocol for delegates to conform to in order to receive callbacks in changes to
 * the calibration state.
 */
@protocol RUICalibrateButtonGestureHandlerProtocol <NSObject>
@optional
/*!
 * Called when a gesture is first recognized to see if calibration should be allowed
 * @param sender - The RUICalibrateButtonGestureHandler asking for permission
 * @return If the calibration should be allowed, defaults to YES
 */
-(BOOL)calibrateGestureHandlerShouldAllowCalibration:(RUICalibrateButtonGestureHandler*)sender;

/*!
 * Called when a calibration gesture begins successfully
 */
-(void)calibrateGestureHandlerBegan:(RUICalibrateButtonGestureHandler*)sender;

/*!
 * Called when a calibration gesture ends successfully
 */
-(void)calibrateGestureHandlerEnded:(RUICalibrateButtonGestureHandler*)sender;

@end
