//
//  RUIColorBrightnessView.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>


/*!
 * @brief View to show the brightness gradient in an arc next to the color-wheel.
 */
@interface RUIColorBrightnessView : UIView {
	@private
    CGMutablePathRef arcPath;
    CGGradientRef brightnessGradient;
    CGFloat arcWidth;
}

/*!
 * Get the inner radius of the brightness selector arc.
 * This is used by the color picker control to correctly place the indicator.
 */
-(CGFloat) arcInnerRadius;

/*!
 * Get the outer radius of the brightness selector arc.
 * This is used by the color picker control to correctly place the indicator.
 */
-(CGFloat) arcOuterRadius;

/*!
 * Update the hue and saturation for the brightness arc to give a better
 * representation of what the user is changing.
 */
-(void) updateHue:(CGFloat)h saturation:(CGFloat)s;

@end
