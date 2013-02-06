//
//  ViewController.h
//  Locator
//
//  Created by Michael DePhillips on 7/12/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>

@interface ViewController : UIViewController {
    BOOL ledON;
    BOOL robotOnline;

    RUICalibrateGestureHandler *calibrateHandler;
}

@property (retain, nonatomic) IBOutlet UITextField *textFieldNewX;
@property (retain, nonatomic) IBOutlet UITextField *textFieldNewY;
@property (retain, nonatomic) IBOutlet UITextField *textFieldNewYaw;

@property (retain, nonatomic) IBOutlet UISwitch *flagSwitch;

@property (retain, nonatomic) IBOutlet UILabel *xValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *yValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *xVelocityValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *yVelocityValueLabel;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(void)startLocatorStreaming;
-(IBAction)configurePressed:(id)sender;
-(IBAction)upPressed:(id)sender;
-(IBAction)downPressed:(id)sender;
-(IBAction)leftPressed:(id)sender;
-(IBAction)rightPressed:(id)sender;
-(IBAction)stopPressed:(id)sender;

@end

