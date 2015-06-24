//
//  RUIHorizontalIndicatorView.h
//  RobotUIKit
//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

/*!
 * Internal view that draws the brightness selection indicator for the color
 * picker view.
 */
@interface RUIHorizontalIndicatorView : UIView {
	@private
	CGFloat indicatorHeight;
	CGFloat indicatorWidth;
}

@property (nonatomic) CGFloat indicatorHeight;
@property (nonatomic) CGFloat indicatorWidth;

@end
