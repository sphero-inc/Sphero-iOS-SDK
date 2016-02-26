//
//  ConfigurationViewController.m
//  CollisionDetection
//
//  Created by Brian Smith on 2/29/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>
#import "ConfigurationViewController.h"

@implementation ConfigurationViewController

- (void)startCollisionDetection:(id)sender
{
    NSString *feildText = nil;
    uint8_t xThreshold = 90;
    uint8_t yThreshold = 90;
    uint8_t xSpeedThreshold = 130;
    uint8_t ySpeedThreshold = 130;
    float deadZone = 1.0f;
    
    feildText = self.xThresholdTextField.text;
    if ([feildText length] > 0) {
        xThreshold = [feildText integerValue];
    }
    feildText = self.yThresholdTextField.text;
    if ([feildText length] > 0) {
        yThreshold = [feildText integerValue];
    }
    feildText = self.xSpeedThresholdTextField.text;
    if ([feildText length] > 0) {
        xSpeedThreshold = [feildText integerValue];
    }
    feildText = self.ySpeedThresholdTextField.text;
    if ([feildText length] > 0) {
        ySpeedThreshold = [feildText integerValue];
    }
    feildText = self.deadZoneTimeTextField.text;
    if ([feildText length] > 0) {
        deadZone = [feildText floatValue];
    }
    
    // start collision detection messages    
//    [RKConfigureCollisionDetectionCommand sendCommandForMethod:RKCollisionDetectionMethod1
//                                                    xThreshold:xThreshold
//                                               xSpeedThreshold:xSpeedThreshold
//                                                    yThreshold:yThreshold
//                                               ySpeedThreshold:ySpeedThreshold
//                                              postTimeDeadZone:deadZone];
//    
    [self dismissModalViewControllerAnimated:YES];
}

#pragma mark - View lifecycle

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

@end
