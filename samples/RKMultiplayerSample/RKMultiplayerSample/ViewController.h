//
//  ViewController.h
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//
//
//  Table view controller that shows the available games to join

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import <RobotKit/RobotKit.h>

@interface ViewController : UITableViewController <RKMultiplayerDelegateProtocol> {
    BOOL ledON;
    BOOL robotOnline;
    RUICalibrateGestureHandler *calibrateHandler;
    NSArray *games;
}

@property (nonatomic, retain) NSArray *games;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(void)toggleLED;

@end

