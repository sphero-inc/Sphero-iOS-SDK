//
//  ViewController.h
//  OrbBasicLoader
//
//  Created by Brian Smith on 10/1/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>

@class OrbBasicFile;

@interface ViewController : UIViewController <UITableViewDataSource, UITableViewDelegate> {
    UITableView                 *filesTableView;
    UITextView                  *messageView;
    
    UIButton                    *appendButton;
    UIButton                    *executedButton;
    UIButton                    *abortButton;
    UIButton                    *eraseButton;
    
    BOOL                        robotOnline;
    BOOL                        connectionSetupFinished;
    RKOrbBasicProgram           *orbBasicProgram;
    
    RUICalibrateGestureHandler  *calibrateHandler;
}

@property (nonatomic, retain) IBOutlet UITableView   *filesTableView;
@property (nonatomic, retain) IBOutlet UITextView    *messageView;

@property (nonatomic, retain) IBOutlet UIButton     *appendButton;
@property (nonatomic, retain) IBOutlet UIButton     *executeButton;
@property (nonatomic, retain) IBOutlet UIButton     *abortButton;
@property (nonatomic, retain) IBOutlet UIButton     *eraseButton;

- (IBAction)load:(id)sender;
- (IBAction)execute:(id)sender;
- (IBAction)abort:(id)sender;
- (IBAction)erase:(id)sender;

- (void)handleResponse:(RKDeviceResponse *)response;
- (void)handleAsyncData:(RKDeviceAsyncData *)data;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
- (void)handleRobotOffline;
- (void)handleRobotDidLoseControl:(NSNotification *)notification;
- (void)handleRobotDidGainControl:(NSNotification *)notification;

@end

