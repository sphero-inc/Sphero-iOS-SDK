//
//  RUIColorPickerViewController.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RUIModalLayerViewController.h>
#import <RobotUIKit/RUIHSBColorPickerView.h>

static NSString *RUIColorPickerViewControllerRGBPickerDisplayedNotification = @"RUIColorPickerViewControllerRGBPickerDisplayedNotification";

@class RUIColorIndicatorView;

@protocol RUIColorPickerDelegate;

/**
 * @brief View controller that allows the user to select a color and brightness.
 *
 * This view controller is made to popup a modal color picker view over an existing view.
 * Assigning a delegate to the controller gives immediate feedback as the user selects a 
 * color for the robot LEDs and can be used to save the selected color in the app
 * preferences and to change the robot LED color.
 */
@interface RUIColorPickerViewController : RUIModalLayerViewController <RUIHSBColorPickerDelegate> {
	
	@private
	NSBundle*               resourceBundle;

	RUIHSBColorPickerView*  colorPickerView;
	RUIColorIndicatorView*  newColorIndicatorView;
	RUIColorIndicatorView*  oldColorIndicatorView;
	UIImageView*			rgbBackgroundView;
	UILabel*                redLabel;
	UILabel*                greenLabel;
	UILabel*                blueLabel;
	
	UIImageView*			colorIndicatorBG;
	UIImageView*			rgbBG;
	UILabel*				colorPickerLabel;
	UIButton*				rollButton;
    IBOutlet UILabel*       rollLabel;
    UIButton*               backButton;
    IBOutlet UILabel*       backLabel;
											  
	id						rgbPicker;
	id                      rgbListener;
	
	CGFloat                 pickedRed;
	CGFloat                 pickedGreen;
	CGFloat                 pickedBlue;
	
	id<RUIColorPickerDelegate> delegate;
	BOOL                       isChangeDelegate;
    BOOL                       showBackButton;
    BOOL                       showRollButton;
    id                         backButtonTarget;
    SEL                        backButtonAction;
}

/*! The view holding the color wheel image that allows the user to see the full spectrum of colors. */
@property (nonatomic, retain) IBOutlet RUIHSBColorPickerView*  colorPickerView;
/*! The view showing the currently selected color and brightness. */
@property (nonatomic, retain) IBOutlet RUIColorIndicatorView*  newColorIndicatorView;
/*! The view showing the original color that the picker started with.  A user tap on this
 *  view will restore the initial color. */
@property (nonatomic, retain) IBOutlet RUIColorIndicatorView*  oldColorIndicatorView;
/*! An image background for the RGB labels.  When double-tapped, this will
    switch to the RGB slider color picker. */
@property (nonatomic, retain) IBOutlet UIImageView*            rgbBackgroundView;
/*! A label showing the red value of the current color in the RGB color space. */
@property (nonatomic, retain) IBOutlet UILabel*                redLabel;
/*! A label showing the green value of the current color in the RGB color space. */
@property (nonatomic, retain) IBOutlet UILabel*                greenLabel;
/*! A label showing the blue value of the current color in the RGB color space. */
@property (nonatomic, retain) IBOutlet UILabel*                blueLabel;
/*! Background image for where the RGB values are displayed. */
@property (nonatomic, retain) IBOutlet UIImageView *colorIndicatorBG, *rgbBG;
/*! A label with the title for the view. */
@property (nonatomic, retain) IBOutlet UILabel *colorPickerLabel;
/*! A button that is on the top right to return to dismiss the dialog to main view. */
@property (nonatomic, retain) IBOutlet UIButton *rollButton;
/*! A button for going back in the view navigation. */
@property (nonatomic, retain) IBOutlet UIButton *backButton;

/*! A delegate that optionally receives notification whenever the user changes the color
 *  or when the user is done picking a color. */
@property (nonatomic, assign) id<RUIColorPickerDelegate> delegate;

/*!
 * Set the color in the color picker.  This can be used to initialize the color
 * picker to the last chosen color.  The 'oldColorIndicatorView' is changed to reflect
 * this color value and the current color is changed as well.
 *
 * @param r The red component of the color, between 0.0 and 1.0
 * @param g The green component of the color, between 0.0 and 1.0
 * @param b The blue component of the color, between 0.0 and 1.0
 */
- (void)setRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*! 
 * Set the current color in the color picker.
 *
 * @param r The red component of the color, between 0.0 and 1.0
 * @param g The green component of the color, between 0.0 and 1.0
 * @param b The blue component of the color, between 0.0 and 1.0
 */
- (void)setCurrentRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b;

/*!
 * This action is used to notify the color-picker that the user has selected a color and
 * the modal view can be removed.  The delegate, if set, is optionally notified of this
 * acction through a call to the 'colorPickerDidFinish' method.
 *
 * @param sender The object that invoked this action.
 */
- (IBAction)done:(id)sender;

/*!
 * This action is used to show or hide the back button in the color picker.
 * By default the back button is hidden and must be shown if it is desired.
 *
 * @param show Whether or not the back button should be shown.
 */
- (void)showBackButton:(BOOL)show;

/*!
 * This action is used to show or hide the roll button and the label below.
 * By default the roll button is shown and must be hidden if desired
 *
 * @param show Set whether or not the roll button should be shown
 */
-(void)showRollButton:(BOOL)show;

/*!
 * Set the target and action to be called when the user taps the back button.
 *
 * @param target The target to be called when the user taps the back button.
 * @param action The action to be called when the user taps the back button.
 */
- (void)setBackButtonTarget:(id)target action:(SEL)action;

//Used to tell controller to layout views for appropriate orientation
-(void)layoutPortrait;
-(void)layoutLandscape;

@end

