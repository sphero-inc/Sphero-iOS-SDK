//
//  TouchNGoController.h
//  OSGIPhone
//
//  Created by Fabrizio Polo on 7/18/12.
//  Copyright (c) 2012 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TouchNGoController : NSObject

    bool touchAndGoIsOn;
    float startFromX, startFromY;
    float goToX, goToY;
    int touchAndGoState;
    float touchAndGoRollHeading;
    float touchAndGoDistanceToTravel;
    //  Touch'n'Go Timing
    double touchAndGoRotationStartTime;
    double touchAndGoDriveStartTime;
    double touchAndGoTimeout;

@end

-(void) init;

-(void) initiateRollingTo:(CGPoint) location;

-(void) stopControlling;

-(float) getTouchAndGoHeadingFromSpheroX:(float)spherox Y:(float) spheroy;

-(float) getTouchAndGoVelocity:(float) distance;

-(void) update: (double) time;

