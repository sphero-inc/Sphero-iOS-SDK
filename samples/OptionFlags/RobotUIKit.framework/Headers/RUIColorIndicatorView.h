//
//  RUIColorIndicatorView.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
 * @brief Show a color in a rounded rectangle.
 */
@interface RUIColorIndicatorView : UIView {
   @private
   CGMutablePathRef drawPath;
   CGColorRef drawColor;
   CGFloat hue;
   CGFloat saturation;
   CGFloat brightness;
}

/*! Get the hue value of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat hue;
/*! Get the saturation value of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat saturation;
/*! Get the brightness value of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat brightness;

/*! Get the red component of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat red;
/*! Get the green component of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat green;
/*! Get the blue component of the displayed color, between 0.0 and 1.0 */
@property (nonatomic, readonly) CGFloat blue;

/*! Initializes objects to default values. */
-(void) initDefaults;

/*!
 * Update the displayed color to reflect the values given.
 *
 * @param h The hue value for the color to display, between 0.0 and 1.0
 * @param s The saturation value for the color to display, between 0.0 and 1.0
 * @param b The brightness value for the color to display, between 0.0 and 1.0
 */
-(void) updateHue:(CGFloat)h saturation:(CGFloat)s brightness:(CGFloat)b;

/*! 
 * Update the displayed color to reflect the values given.
 *
 * @param r The red component value for the color to display, between 0.0 and 1.0
 * @param g The green component value for the color to display, between 0.0 and 1.0
 * @param b The blue component value for the color to display, between 0.0 and 1.0
 */
-(void) updateRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*!
 * Call this to have the view listen for color change notifications from RUColorPickerViewController
 * and have it auto update it's color upon change.
 */
-(void) autoUpdateColor;


@end
