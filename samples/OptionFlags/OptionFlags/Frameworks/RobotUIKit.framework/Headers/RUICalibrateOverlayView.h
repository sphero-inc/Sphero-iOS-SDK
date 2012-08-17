//
//  RUICalibrateOverlayView.h
//  SpheroDraw
//
//  Created by Jon Carroll on 11/4/11.
//  Copyright (c) 2011 Orbotix. All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
 * @brief A view that can be overlayed to show a rotation gesture is happening
 *
 * Instead of using this class directly consider using the RUICalibrateGestureHandler class
 * that will handle displaying this overlay automatically.
 * @see RUICalibrateGestureHandler
 */
@interface RUICalibrateOverlayView : UIView {
    @private
    UIImageView *outerRing, *middleRing, *innerRing;
    UIImageView *dot1, *dot2;
    BOOL animating;
    CGPoint point1, point2;
    float innerRotation, outerRotation;
    float rotationDif, lastRotation, currentRotation;
}

/*!
 * Use this initializer to have the rings animate in properly
 * @param frame The rect of the screen this will be displayed as an overlay on
 * @return The instace of this class
 */
-(id)initWithFrame:(CGRect)frame;

/*!
 *  Should be called as the touches are processed and the gesture is recognized to animate the overlay
 *  @param p1 The location of the first touch in screen coordinates
 *  @param p2 The location of the second touch in screen coordinates
 *  @param rotation The rotation of the gesture since the last call to this method (will animate rings)
 */
-(void)point1Moved:(CGPoint)p1 point2Moved:(CGPoint)p2 withRotation:(float)rotation;

/*!
 *  Called when the touch gesture ends to make the rings animate out
 */
-(void)calibrationDone;

@end
