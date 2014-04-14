//
//  RUIColorPickerDelegate.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/*! 
 * @brief Protocol to be implemented by classes wishing to receive information
 *        from the RobotUIKit color pickers.
 */
@protocol RUIColorPickerDelegate <NSObject>

@optional
/*!
 * This method is called whenever the current color in the color-picker changes.
 *
 * @param controller The color-picker view controller sending the message.
 * @param r The red component of the current color, between 0.0 and 1.0
 * @param g The green component of the current color, between 0.0 and 1.0
 * @param b The blue component of the current color, between 0.0 and 1.0
 */
-(void) colorPickerDidChange:(UIViewController*)controller 
					 withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*!
 * This method is called when the user has indicated that they are done with the
 * color-picker and the current color is the one that should be used.
 *
 * @param controller The color-picker view controller sending the message.
 * @param r The red component of the current color, between 0.0 and 1.0
 * @param g The green component of the current color, between 0.0 and 1.0
 * @param b The blue component of the current color, between 0.0 and 1.0
 */
-(void) colorPickerDidFinish:(UIViewController*)controller 
					 withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

@end
