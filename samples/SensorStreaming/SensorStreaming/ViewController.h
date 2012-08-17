//
//  ViewController.h
//  SensorStreaming
//
//  Created by Brian Smith on 03/28/12.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RKDeviceAsyncData;

@interface ViewController : UIViewController {
    BOOL robotOnline;
    int  packetCounter;
    
    UILabel *xValueLabel;
    UILabel *yValueLabel;
    UILabel *zValueLabel;
    UILabel *pitchValueLabel;
    UILabel *rollValueLabel;
    UILabel *yawValueLabel;
}

@property (nonatomic, retain) IBOutlet UILabel *xValueLabel;
@property (nonatomic, retain) IBOutlet UILabel *yValueLabel;
@property (nonatomic, retain) IBOutlet UILabel *zValueLabel;
@property (nonatomic, retain) IBOutlet UILabel *pitchValueLabel;
@property (nonatomic, retain) IBOutlet UILabel *rollValueLabel;
@property (nonatomic, retain) IBOutlet UILabel *yawValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *q0ValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *q1ValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *q2ValueLabel;
@property (retain, nonatomic) IBOutlet UILabel *q3ValueLabel;

-(void)setupRobotConnection;
-(void)handleRobotOnline;
-(void)handleAsyncData:(RKDeviceAsyncData *)asyncData;
-(void)sendSetDataStreamingCommand;

@end

