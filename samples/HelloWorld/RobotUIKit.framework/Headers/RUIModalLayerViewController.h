//
//  RUIModalLayerViewController.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RUIModalLayerViewController;

/*!
 * @brief Base class for view controllers that wish to be shown modally on top of their
 * parent views.
 *
 * View controllers derived from this class will completely cover their parent views
 * with an optionally semi-transparent 'glass' covering so that the parent view is
 * blocked.  The user can then only interact with the modal view until it is
 * dismissed.
 *
 * If you want the modalLayerViewController to automatically rotate to the proper orientation
 * you must pass all willAnimateRotationToInterfaceOrientation:duration: to th modal layer
 * view controller.
 *
 */
@interface RUIModalLayerViewController : UIViewController {
    @private
    CGFloat  backgroundAlpha;
    UIColor *backgroundColor;
	id       dismissedTarget;
	SEL      dismissedAction;
	UIView	*parentView;
}

/*! The alpha channel value for the 'glass' covering the parent view. */
@property (nonatomic, assign) CGFloat backgroundAlpha;
/*! The color of the 'glass' covering the parent view. */
@property (nonatomic, copy)   UIColor *backgroundColor;

/*! Get the currently active modal layer view controller. */
+ (RUIModalLayerViewController *)currentModalLayerViewController;

/*!
 * Dismiss this modal layer view controller so that the parent view is available
 * for interaction.
 *
 * @param animated Whether or not the dismissal of this view should be animated.
 */
- (void)dismissModalLayerViewControllerAnimated:(BOOL)animated;

/*!
 * Called by the framework to add a semi-transperant background and center the
 * content view to the parent's bounds.  This method can be overridden by
 * subclasses to provide a different background for the modal view.
 *
 * @param parentViewController The modal layer's content view.
 *
 * @return The final modal view that will be embedded into the parent view.
 */
- (UIView *)layerViewForParentViewController:(UIViewController *)parentViewController;

/*!
 * Set a target object and action to be called when the modal view controller
 * has been dismissed.  The action is called with this view controller as its
 * only argument.
 *
 * @param target The target to send the completion action to.
 * @param action The action to perform on the target when this modal view
 *               controller has been dismissed.
 */
- (void) setDismissedTarget:(id)target action:(SEL)action;

/*! Should be implemented in subclass to layout view in landscape. */
-(void)layoutPortrait;

/*! Should be implemented in subclass to layout view in portrait. */
-(void)layoutLandscape;

@end

/*!
 * Additions to the UIViewController class to present our modal layer view
 * controllers correctly.
 */
@interface UIViewController (RUIModalLayerAdditions)

/*!
 * Present a modal layer view controller over this controller's view.  The 
 * controller being presented as modal will cover this entire view controller
 * with a semi-transparent 'glass' layer and center the modal view.
 *
 * @param modalViewController The modal view to present over this one.
 * @param animated Whether or not the presentation of the modal view should be
 *                 animated.
 */
- (void)presentModalLayerViewController:(RUIModalLayerViewController *)modalViewController 
                               animated:(BOOL)animated;
@end



