//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EAGLView : UIView

- (void)startAnimation;
- (void)stopAnimation;
- (void)setRotationWithAccelerometerX:(float)x Y:(float)y Z:(float)z;

@end
