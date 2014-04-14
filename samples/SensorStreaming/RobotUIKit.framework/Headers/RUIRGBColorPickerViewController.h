//
//  RUIRGBColorPickerViewController.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RUIModalLayerViewController.h>

@protocol RUIColorPickerDelegate;
@class RUIColorIndicatorView;

/*!
 * @brief View controller that allows the user to select a color using RGB values.
 *
 * This view controller is made to popup a modal color picker view over an existing view.
 * Assigning a delegate to the controller gives immediate feedback as the user selects
 * a color for the robot LEDs and can be used to save the selected color in the app
 * preferences and to change the robot LED color.
 */
@interface RUIRGBColorPickerViewController : RUIModalLayerViewController {

	@private
	UITextField* redTextField;
	UISlider*    redSlider;
	UITextField* greenTextField;
	UISlider*    greenSlider;
	UITextField* blueTextField;
	UISlider*    blueSlider;
	
	RUIColorIndicatorView* oldColorIndicator;
	RUIColorIndicatorView* curColorIndicator;
	
	id<RUIColorPickerDelegate> delegate;
	BOOL                       isChangeDelegate;
	
	CGFloat origRed;
	CGFloat red;
	CGFloat origGreen;
	CGFloat green;
	CGFloat origBlue;
	CGFloat blue;
}

/*! A text field where the user can enter a value for the red color component. */
@property (nonatomic, retain) IBOutlet UITextField* redTextField;
/*! A slider that the user can use to quickly adjust the red color component. */
@property (nonatomic, retain) IBOutlet UISlider*    redSlider;
/*! A text field where the user can enter a value for the green color component. */
@property (nonatomic, retain) IBOutlet UITextField* greenTextField;
/*! A slider that the user can use to quickly adjust the green color component. */
@property (nonatomic, retain) IBOutlet UISlider*    greenSlider;
/*! A text field where the user can enter a value for the blue color component. */
@property (nonatomic, retain) IBOutlet UITextField* blueTextField;
/*! A slider that the user can use to quickly adjust the blue color component. */
@property (nonatomic, retain) IBOutlet UISlider*    blueSlider;

/*! A view showing the original color that the picker started with. A user tap on this
 *  view will retore the initial color values. */
@property (nonatomic, retain) IBOutlet RUIColorIndicatorView* oldColorIndicator;
/*! A view showing the currently selected color */
@property (nonatomic, retain) IBOutlet RUIColorIndicatorView* curColorIndicator;

/*! A delegate that optionally receives notification whenever the user changes the color
 *  or when the user is done picking a color. */
@property (nonatomic, assign) id<RUIColorPickerDelegate> delegate;

/*! 
 * Sets the color in the color picker. This can be used to initialize the color picker
 * to the last chosen color.  The 'oldColorIndicatorView' is changed to reflect
 * this color value and the current color is changed as well.
 *
 * @param r The red component of the color, between 0.0 and 1.0
 * @param g The green component of the color, between 0.0 and 1.0
 * @param b The blue component of the color, between 0.0 and 1.0
 */
- (void)setRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*!
 * Sets the current color in the color picker.
 *
 * @param r The red component of the color, between 0.0 and 1.0
 * @param g The green component of the color, between 0.0 and 1.0
 * @param b The blue component of the color, between 0.0 and 1.0
 */
- (void)setCurrentRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*!
 * Action to be called whenever one of the color component sliders has changed value.
 * This action updates the correct component value text field and updates the 
 * 'curColorIndicator' to reflect the new color.  The delegate, if set, is also
 * optionally notified of the color change through a call to the 'colorPickerDidChange'
 * method.
 *
 * @param slider The slider that changed value.
 */
- (IBAction) sliderChanged:(UISlider*)slider;

/*!
 * Action to be called whenever the user finishes editing the value in one of the
 * color component text fields.  This action updates the position of the component
 * slider and updates the 'curColorIndicator' view to reflect the new color.  The
 * delegate, if set, is also optionally notified of the color change through a
 * call to the 'colorPickerDidChange' method.
 *
 * @param textField The textfield that was changed.
 */
- (IBAction) rgbDidEndEditing:(UITextField*)textField;

/*!
 * Action to be called when the user is done picking a color. The delegate, if set,
 * is optionally notified of the action through a call to the 'colorPickerDidFinish'
 * method.
 *
 * @param sender The control that sent this action.
 */
- (IBAction) done:(id)sender;

@end
