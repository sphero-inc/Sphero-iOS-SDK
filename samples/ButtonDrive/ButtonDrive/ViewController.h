//
//  ViewController.h
//  ButtonDrive
//
//  Created by Jon Carroll on 12/9/11.
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

//Interface interactions
-(IBAction)zeroPressed:(id)sender;
-(IBAction)ninetyPressed:(id)sender;
-(IBAction)oneEightyPressed:(id)sender;
-(IBAction)twoSeventyPressed:(id)sender;
-(IBAction)stopPressed:(id)sender;

@end

