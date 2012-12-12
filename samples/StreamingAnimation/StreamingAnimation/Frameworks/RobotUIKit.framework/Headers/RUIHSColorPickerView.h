//
//  RUIHSBColorPickerView.h
//  RobotUIKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RUIHSColorPickerData;

@protocol RUIHSColorPickerDelegate;

/*!
 * @brief View class showing an HSB color wheel and brightness slider that
 *        allows the user to select a specific color.
 *
 * The user can tap the color wheel or brightness slider or can drag the
 * crosshairs and brightness slider around to change colors.
 */
@interface RUIHSColorPickerView : UIView <UIGestureRecognizerDelegate> {
	@private
	RUIHSColorPickerData* data;
}

/*! The color currently selected in the color picker. */
@property (nonatomic, copy) UIColor* value;

/*! The receiver's delegate. */
@property (nonatomic, assign) id<RUIHSColorPickerDelegate> delegate;

/*! Shows brightness slider, defaults to YES */
@property BOOL showsBrightnessSlider;

/*!
 * Set the color picker's current color using the values for hue,
 * saturation and brightness.
 * 
 * @param h The value for the color's hue - between 0.0 and 1.0
 * @param s The value for the color's saturation - between 0.0 and 1.0
 * @param b The value for the color's brightness - between 0.0 and 1.0
 */
- (void)setHue:(CGFloat)h saturation:(CGFloat)s brightness:(CGFloat)b;

/*!
 * Set the color picker's current color using the values for red, green
 * and blue.
 *
 * @param r The value for the color's red component - between 0.0 and 1.0
 * @param g The value for the color's green component - between 0.0 and 1.0
 * @param b The value for the color's blue component - between 0.0 and 1.0
 */
- (void)setRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

@end

/*!
 * @brief Protocol for the color picker view delegate to implement.
 *
 * The delegate is notified whenever the color in the color picker changes.
 */
@protocol RUIHSColorPickerDelegate <NSObject>

/*!
 * Called when the color picker view's selected color changes.
 *
 * @param view The color picker view that changed
 * @param r The red component of the color
 * @param g The green component of the color
 * @param b The blue component of the color
 */
- (void)colorPickerDidChange:(RUIHSColorPickerView*)view 
					 withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

@end