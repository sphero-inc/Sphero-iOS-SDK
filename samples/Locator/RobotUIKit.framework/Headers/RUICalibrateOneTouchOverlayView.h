//
//  RUICalibrateOneTouchOverlayView.h
//
//  Created by Mike DePhillips on 10/24/12.
//  Copyright (c) 2011 Orbotix. All rights reserved.
//

#import "RUICalibrateButtonGestureHandler.h"
#import <UIKit/UIKit.h>

/*!
 * @brief A view that can be overlayed to show a rotation gesture is happening
 *
 * Instead of using this class directly consider using the RUICalibrateGestureHandler class
 * that will handle displaying this overlay automatically.
 * @see RUICalibrateGestureHandler
 */
@interface RUICalibrateOneTouchOverlayView : UIView {
    @private
    UIImageView *outerRing, *middleRing, *innerRing;
    UIImageView *dot;
    BOOL animating;
    CGPoint currentPoint, previousPoint;
    CGPoint startPoint;
    int calibrationRadius;
    RUICalibrationCircleLocation calibrationCircleLocation;
}

/*!
 *  Should be called as the touches are processed and the gesture is recognized to animate the overlay
 *  @param p1 The location of the first touch in screen coordinates
 */
-(void)currentPointMoved:(CGPoint)p1;

/*!
 *  Called when the touch gesture ends to make the rings animate out
 */
-(void)calibrationDone;

/*!
 * Use this initializer to have the rings animate in properly
 * @param frame The rect of the screen this will be displayed as an overlay on
 * @param aStartPoint the x,y coordinates of the first touch event
 * @param radius the size of the radius in pixels
 * @param location where the calibration circle is drawn with respect to the button
 * @return The instace of this class
 */
- (id)initWithFrame:(CGRect)frame
         StartPoint:(CGPoint)aStartPoint
             Radius:(int)radius
           Location:(RUICalibrationCircleLocation)location;

@end
