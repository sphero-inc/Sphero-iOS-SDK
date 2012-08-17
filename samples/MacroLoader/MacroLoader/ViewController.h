//
//  ViewController.h
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import <RobotKit/RobotKit.h>


@interface ViewController : UIViewController {
    BOOL robotOnline;
}

-(IBAction)macro1:(id)sender;
-(IBAction)macro2:(id)sender;
-(IBAction)macro3:(id)sender;
-(IBAction)macro4:(id)sender;
-(IBAction)stop:(id)sender;

-(void)setupRobotConnection;
-(void)handleRobotOnline;

@end

