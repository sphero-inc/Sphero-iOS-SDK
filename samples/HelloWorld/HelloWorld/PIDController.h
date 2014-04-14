//
//  PIDController.h
//  HelloWorld
//
//  Created by Michael DePhillips on 5/25/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PIDController : NSObject {
    double errorSumX;
    double errorSumY;
    double currentErrorX;
    double currentErrorY;
    double previousErrorX;
    double previousErrorY;
    
    double targetValueX;
    double targetValueY;
    
    bool trackX; 
    bool countUp;
}

@property double errorSumX;
@property double errorSumY;
@property double currentErrorX;
@property double currentErrorY;
@property double previousErrorX;
@property double previousErrorY;
@property double targetValueX;
@property double targetValueY;
@property bool countUp;

-(double) computeControlVariableFromX:(double)x Y:(double)y;
-(void) initializeControllerFromTargetX:(double)tx TargetY:(double)ty trackingX:(BOOL)isTX;
-(PIDController*) init;

@end
