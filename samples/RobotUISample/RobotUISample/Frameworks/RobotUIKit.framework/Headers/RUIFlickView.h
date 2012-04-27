//
//  RUIFlickView.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RUIFlickGestureRecognizer;

/*!
 * @brief View class showing a "puck" that responds to flicking gestures from the user.
 * 
 * When the puck is flicked, any specified targets receive an action call where they can
 * check for the speed and heading of the puck.
 */
@interface RUIFlickView : UIView {
	@private
	UIImageView			*puckView;
    CGAffineTransform	puckTransform;
    double              radius;
    double              speed;
    double              heading;
    
    NSMutableArray      *targets;
    NSMutableArray      *actions;
    
    RUIFlickGestureRecognizer  *flickGestureRecognizer;
}

/*! The current relative speed of the puck. */
@property (nonatomic, readonly) double speed;
/*! The heading of the puck in radians (see atan2) */
@property (nonatomic, readonly) double heading;

/*! 
 * Add a target object that performs the given selector when the puck is flicked.
 *
 * @param target The target object to send the selector to when the puck is flicked.
 * @param action The selector to call on the target when the puck is flicked.
 *               The selector should take a single argument that is the flick
 *               view that caused the selector to be called.
 */
- (void)addTarget:(id)target action:(SEL)action;

/*!
 * Set the puck image to the given image.
 *
 * @param image The image to show on the puck.
 */
- (void)setPuckImage:(UIImage*)image;

/*!
 * Used to disable the flick guesture recognizer so you can do other detection
 * with the puck.
 */
- (void)setFlickEnabled:(BOOL)enabled;

/*!
 * Used in subclasses to override common behaviors.  Be sure to call [super commonInit]
 * 
 */
- (void)commonInit;

/*!
 *  Used to get the gesture recognizer in case you need to require other recognizers to fail
 */
-(RUIFlickGestureRecognizer*)getRecognizer;

@end
