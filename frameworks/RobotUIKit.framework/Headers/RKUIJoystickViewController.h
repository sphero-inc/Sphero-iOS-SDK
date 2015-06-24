//
//  RKUIJoystickViewController.h
//  RobotUIKit
//
//  Created by Corey Earwood on 1/2/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol RKUIJoystickViewControllerDelegate <NSObject>

- (void)joystickDidMoveWithHeading:(float)heading andVelocity:(float)velocity;
- (void)joystickDidStop;

@end

@interface RKUIJoystickViewController : UIViewController

@property (nonatomic, weak) id<RKUIJoystickViewControllerDelegate> joystickDelegate;

- (void)enableJoystick;
- (void)disableJoystick;

@end
