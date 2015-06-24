//
//  Copyright 2010-2015 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RUIModalViewController;

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
@interface RUIModalViewController : UIViewController

/*! Should be implemented in subclass to layout view in landscape. */
- (void)layoutPortrait;

/*! Should be implemented in subclass to layout view in portrait. */
- (void)layoutLandscape;

@end
