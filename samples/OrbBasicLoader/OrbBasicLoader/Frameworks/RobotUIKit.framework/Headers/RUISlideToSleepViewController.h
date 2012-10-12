//
//  RUISlideToSleepViewController.h
//  RobotUIKit
//
//  Created by Jon Carroll on 10/3/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RUIModalLayerViewController.h"

@protocol RUISlideToSleepViewControllerDelegate;

/*!
 *  @brief A view controller to present when allowing the user to put Sphero to sleep
 *
 *  This view will dim the screen and animate in a "slide to sleep" slider at the top of the screen
 *  When the user moves the slider this view will automatically put Sphero to sleep
 *  If the user taps in the dim area outside the slider it will cancel the operatipon and animate the slider out
 *  
 *  There are delegate callbacks on success and failure
 */
@interface RUISlideToSleepViewController : RUIModalLayerViewController {
    @private
    id<RUISlideToSleepViewControllerDelegate> delegate;
    IBOutlet UIImageView *sliderBG;
    IBOutlet UIImageView *sliderArrow;
}

/*! Delegate that will recieve callbacks on success or failure */
@property (nonatomic, assign) id<RUISlideToSleepViewControllerDelegate> delegate;

@end

/*!
 * Protocol that a delegate conforms to in order to receive callbacks to confirm sleep
 * or cancel it.
 */
@protocol RUISlideToSleepViewControllerDelegate <NSObject>
@optional
/*!
 * Called after a user has slid the sleep slider all the way over, a sleep command is automatically send to the robot before this callback
 * @param sender The object that called the method.
 */
-(void)slideToSleepConfirmed:(id)sender;
/*! 
 * A user touched outside of the sleep slider canceling the action
 * @param sender The object that called the method.
 */
-(void)slideToSleepCanceled:(id)sender;
@end