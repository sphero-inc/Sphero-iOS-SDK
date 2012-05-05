//
//  ConfigurationViewController.h
//  CollisionDetection
//
//  Created by Brian Smith on 2/29/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ConfigurationViewController : UIViewController {
    // configuration UI
    UIView      *configurationView;
    UITextField *xThresholdTextField;
    UITextField *yThresholdTextField;
    UITextField *xSpeedThresholdTextField;
    UITextField *ySpeedThresholdTextField;
    UITextField *deadZoneTimeTextField;
    UIButton    *startButton;
}

// configuration UI
@property (nonatomic, retain) IBOutlet UITextField  *xThresholdTextField;
@property (nonatomic, retain) IBOutlet UITextField  *yThresholdTextField;
@property (nonatomic, retain) IBOutlet UITextField  *xSpeedThresholdTextField;
@property (nonatomic, retain) IBOutlet UITextField  *ySpeedThresholdTextField;
@property (nonatomic, retain) IBOutlet UITextField  *deadZoneTimeTextField;
@property (nonatomic, retain) IBOutlet UIButton     *startButton;

- (IBAction)startCollisionDetection:(id)sender;

@end
