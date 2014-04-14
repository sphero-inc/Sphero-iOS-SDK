//
//  RUICalibrateGestureHandler.h
//  RobotUIKit
//
//  Created by Jon Carroll on 11/28/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class RUICalibrateGestureHandler;
@protocol RUICalibrateGestureHandlerProtocol;

/*!
 *@brief Class to add a rotation gesture recognizer to a view and automatically display
 * the rotation rings on the furthest superview
 */
@interface RUICalibrateGestureHandler : NSObject {
    id <RUICalibrateGestureHandlerProtocol> delegate;
    @private
    UIView *view, *targetView;
    UIRotationGestureRecognizer *recognizer;
    CGPoint lastTouch2;
}

/*!
 *  Delegate that will be notified when calibration begins and ends so sounds can be played
 */
@property (nonatomic, assign) id <RUICalibrateGestureHandlerProtocol> delegate;

/*!
 *  @param view - the view that you want the gesture recognizer to be added to
 */
-(id)initWithView:(UIView*)view;

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

@end

/*!
 * Protocol for delegates to conform to in order to receive callbacks in changes to
 * the calibration state.
 */
@protocol RUICalibrateGestureHandlerProtocol <NSObject>
@optional
/*!
 * Called when a gesture is first recognized to see if calibration should be allowed
 * @param sender - The RUIcalibrateGestureHandler asking for permission
 * @return If the calibration should be allowed, defaults to YES
 */
-(BOOL)calibrateGestureHandlerShouldAllowCalibration:(RUICalibrateGestureHandler*)sender;

/*!
 * Called when a calibration gesture begins successfully
 */
-(void)calibrateGestureHandlerBegan:(RUICalibrateGestureHandler*)sender;

/*!
 * Called when a calibration gesture ends successfully
 */
-(void)calibrateGestureHandlerEnded:(RUICalibrateGestureHandler*)sender;

@end
