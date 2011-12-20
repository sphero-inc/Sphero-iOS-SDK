//
//  ViewController.h
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController {
    BOOL ledON;
    BOOL robotOnline;
}

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(void)toggleLED;

@end

