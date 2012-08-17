//
//  ViewController.h
//  SelfLevel
//
//  Created by Michael DePhillips on 7/14/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>

@interface ViewController : UIViewController {

    BOOL robotOnline;
}

@property (retain, nonatomic) IBOutlet UISwitch *headingSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *sleepSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *controlSystemSwitch;

@property (retain, nonatomic) IBOutlet UILabel *selfLevelStatusLabel;

@property (retain, nonatomic) IBOutlet UITextField *angleLimitTextField;
@property (retain, nonatomic) IBOutlet UITextField *timeoutTextField;
@property (retain, nonatomic) IBOutlet UITextField *accuracyTextField;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(IBAction)selfLevelPressed:(id)sender;
-(IBAction)abortPressed:(id)sender;
-(IBAction)dismissKeyboard:(id)sender;

@end

