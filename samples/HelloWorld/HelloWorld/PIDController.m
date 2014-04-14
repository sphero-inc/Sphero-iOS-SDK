//
//  PIDController.m
//  HelloWorld
//
//  Created by Michael DePhillips on 5/25/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//

#import "PIDController.h"

static double P_CONSTANT = 0.04;
static double MIN_POWER = 0.30;
static double CM_OVERSHOOT_30 = 6.0;

@implementation PIDController 

@synthesize errorSumX;
@synthesize errorSumY;
@synthesize currentErrorX;
@synthesize currentErrorY;
@synthesize previousErrorX;
@synthesize previousErrorY;
@synthesize targetValueX;
@synthesize targetValueY;
@synthesize countUp;

- (id)init
{
    self = [super init];
    if (self)
    {
        // Initialization code here.
        currentErrorX = 0.0;
        currentErrorY = 0.0;
        errorSumX = 0.0;
        errorSumY = 0.0;
        targetValueX = 0.0;
        targetValueY = 0.0;
        trackX = true;
    }
    
    return self;
}

-(void) initializeControllerFromTargetX:(double)tx TargetY:(double)ty trackingX:(BOOL)isTX {
    errorSumX = 0.0;
    errorSumY = 0.0;
    targetValueX = tx + currentErrorX;
    targetValueY = ty + currentErrorY;
    
    countUp = (tx > 0) || (ty > 0);
    
    if( countUp ) {
        targetValueX -= CM_OVERSHOOT_30;
        targetValueY -= CM_OVERSHOOT_30;
    }
    else {
        targetValueX += CM_OVERSHOOT_30;
        targetValueY += CM_OVERSHOOT_30;
    }
    
    trackX = isTX;
}

-(double) computeControlVariableFromX:(double)posX Y:(double)posY {
    
    previousErrorX = currentErrorX;
    previousErrorY = currentErrorY;
    
    if( countUp ) {
        currentErrorX = targetValueX - posX;
        currentErrorY = targetValueY - posY;
    }
    else {
        currentErrorX = posX - targetValueX;
        currentErrorY = posY - targetValueY;
    }
    
    //double derivativeX = currentErrorX - previousErrorX;
    //double derivativeY = currentErrorY - previousErrorY;
    
    errorSumX += currentErrorX;
    errorSumY += currentErrorY;
    
    // For now we test the proportional conroller to be 100% power at distances less than 50 inches
    // Therefore a distance of 0 is 30% power and we stop
    if (trackX) {
        if( currentErrorX < 0.0 ) {
            return -1.0;
        }
        return MAX(currentErrorX * P_CONSTANT, MIN_POWER);
    }
    else {
        if( currentErrorY < 0.0 ) {
            return -1.0;
        }
        return MAX(currentErrorY * P_CONSTANT, MIN_POWER);
    }
}

@end
