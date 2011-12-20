//
//  ViewController.h
//  AchievementSample
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>

@interface ViewController : UIViewController {
    BOOL robotOnline;
    RUICalibrateGestureHandler *calibrateHandler;
}

-(void)setupRobotConnection;
-(void)handleRobotOnline;

//Button press events
-(IBAction)redPressed:(id)sender;
-(IBAction)greenPressed:(id)sender;
-(IBAction)bluePressed:(id)sender;
-(IBAction)spheroWorldPressed:(id)sender;

//Notification when an achievement is earned
-(void)spheroWorldAchievementEarned:(NSNotification*)notification;

@end

