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
    
    float robotSpeed, robotDelay, robotLoop;
    
    UILabel     *speedLabel;
    UILabel     *delayLabel;
    UILabel     *loopLabel;
    
    UISlider    *speedSlider;
    UISlider    *delaySlider;
    UISlider    *loopSlider;
}

@property (nonatomic,retain) IBOutlet UILabel *speedLabel;
@property (nonatomic,retain) IBOutlet UILabel *loopLabel;
@property (nonatomic,retain) IBOutlet UILabel *delayLabel;

@property (nonatomic,retain) IBOutlet UISlider *speedSlider;
@property (nonatomic,retain) IBOutlet UISlider *loopSlider;
@property (nonatomic,retain) IBOutlet UISlider *delaySlider;


-(IBAction) sliderChanged:(id) sender;
-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(IBAction)MacroSquare:(id) sender;
-(IBAction)MacroShape:(id) sender;
-(IBAction)MacroColor:(id) sender;
-(IBAction)AbortMacro:(id) sender;
@end

