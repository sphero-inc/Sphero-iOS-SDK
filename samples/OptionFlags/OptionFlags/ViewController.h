//
//  ViewController.h
//  OptionFlags
//
//  Created by Michael DePhillips on 7/31/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import <RobotKit/RobotKit.h>

@interface ViewController : UIViewController {
    
    BOOL robotOnline;
}

@property (retain, nonatomic) IBOutlet UILabel *bit0Label;
@property (retain, nonatomic) IBOutlet UILabel *bit1Label;
@property (retain, nonatomic) IBOutlet UILabel *bit2Label;
@property (retain, nonatomic) IBOutlet UILabel *bit3Label;
@property (retain, nonatomic) IBOutlet UILabel *bit4Label;
@property (retain, nonatomic) IBOutlet UISwitch *bit0Switch;
@property (retain, nonatomic) IBOutlet UISwitch *bit1Switch;
@property (retain, nonatomic) IBOutlet UISwitch *bit2Switch;
@property (retain, nonatomic) IBOutlet UISwitch *bit3Switch;
@property (retain, nonatomic) IBOutlet UISwitch *bit4Switch;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(void)handleResponse:(RKDeviceResponse *)response;
-(IBAction)getOptionFlagsPressed:(id)sender;
-(IBAction)setOptionFlagsPressed:(id)sender;
-(IBAction)restoreDefaultsPressed:(id)sender;

@end

