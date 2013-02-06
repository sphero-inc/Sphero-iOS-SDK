//
//  ViewController.h
//  SpheroStreaming
//
//  Created by Skylar Castator April 12 2012
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface ViewController : UIViewController <UIAlertViewDelegate>{

    BOOL robotOnline;
    
    //Create labels 
    IBOutlet UILabel* yawLabel;
    IBOutlet UILabel* accelxLabel;
    IBOutlet UILabel* accelyLabel;

    //Sets Sphero's center location
    CGPoint targetSpheroLoc; //Sphero's Center

    //Timer
    NSTimer *randomMain;
    
    //Sphero Image
    IBOutlet UIImageView *sphero;  //Sphero
}
@property(nonatomic, retain) UILabel* IBOutlet yawLabel;
@property(nonatomic, retain) UILabel* IBOutlet accelxLabel;
@property(nonatomic, retain) UILabel* IBOutlet accelyLabel;
@property(nonatomic, retain)  UIImageView *sphero;
@property CGPoint targetSpheroLoc;
@property(nonatomic, retain)  NSTimer *randomMain;

-(void)sendSetDataStreamingCommand;
-(void)setupRobotConnection;
-(void)handleRobotOnline;

-(void)animateSphero;

@end
