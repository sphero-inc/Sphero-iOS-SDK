//
//  RUIFlickGestureRecognizer.h
//  RobotKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <UIKit/UIGestureRecognizerSubclass.h>

/*!
 * @brief Recognize 'flick' gestures and get their heading, speed and distance.
 *
 * This gesture recognizer provides the heading, distance and speed of the flick
 * gesture for use in controlling the robot.  This gesture makes use of the
 * UIGestureRecognizerStateBegan, UIGestureRecognizerStateChanged and 
 * UIGestureRecognizerStateEnded states to provide continuous feedback on the
 * flick gesture that was recognized.
 */
@interface RUIFlickGestureRecognizer : UIGestureRecognizer {
@private
    double          heading;
    CGPoint         translation; // In attach view's coordinates
    double          speed;
    
    NSTimeInterval  timeStamp;
    CGPoint         startLocation;
}

/*! The heading of the flick gesture (in radians, see atan2) */
@property (nonatomic, readonly) double  heading;

/*! The distance from the initial touch point to the end of the flick. */
@property (nonatomic, readonly) CGPoint translation;

/*! The speed of the flick (in points per second) */
@property (nonatomic, readonly) double  speed;

@end
