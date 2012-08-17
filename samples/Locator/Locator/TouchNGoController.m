//
//  TouchNGoController.m
//  OSGIPhone
//
//  Created by Fabrizio Polo on 7/18/12.
//  Copyright (c) 2012 Orbotix. All rights reserved.
//

#import "TouchNGoController.h"

//#include "Aure.h"

@implementation TouchNGoController


-(void) init
{
    touchAndGoIsOn = NO;
    touchAndGoState = 0;
}


-(void) initiateRollingTo:(CGPoint) location
{
    //  Rescale the location coordinates to be in [0,1]
    location.x /= window.frame.size.width;
    location.y /= window.frame.size.height;
    
    location.x = 1.0f - location.x;
    location.y = 1.0f - location.y;
    
    //  F
    float tapSpot[3];
    //  AU_CLIENT
    const bool isInFront = auGet3dFrom2d(CACurrentMediaTime(),
                                         location.y, location.x, 0.0f, tapSpot);
    NSLog(@"Tap detected at %1.2f, %1.2f", tapSpot[0], tapSpot[1]);
    
    //  If the click was above the horizon then just return.
    if (!isInFront)
        return;
    
    //  Turn Tap-n-Go on.
    goToX = tapSpot[0];
    goToY = tapSpot[1];
    touchAndGoIsOn = YES;
    touchAndGoState = 0;
}

-(void) stopControlling
{
    touchAndGoIsOn = NO;
}

-(float) getTouchAndGoHeadingFromSpheroX:(float)spherox Y:(float) spheroy
{
    au_scalar angle = 360.0f - atan2f(goToY - spheroy, goToX - spherox) * 180.0f / M_PI + 90.0f;
    while (angle < 0)
        angle -= 360.0f;
    while (angle >= 360.0f)
        angle -= 360.0f;
    return angle;
}

-(float) getTouchAndGoVelocity:(float) distance
{
    const float rampDownDistance = 0.8f;    //  Start ramping down at this distancde (meters)
    if (distance <= 0)
        return 0.0f;
    else
        if (distance < rampDownDistance)
        {
            const float ratio = distance / rampDownDistance;

            return ratio;
        }
        else {
            return 1.0f;
        }
}

-(void) update: (double) time
{
    if (touchAndGoIsOn)
    {
        switch (touchAndGoState) {
                
            case 0:
            {
                //  Command a stop
                NSLog(@"Touch'N'Go State 0");
                [RKRollCommand sendStop];
                //  Put the reticule where the user clicked
                //const float trailSize = 0.06;
                //osg::Matrix trailScale = osg::Matrix::scale(trailSize, trailSize, trailSize);
                //osg::Matrix trailTranslate = osg::Matrix::translate(osg::Vec3f(-goToY, goToX, 0.0f));
                //touchAndGoReticule->setMatrix(trailScale * trailTranslate);
                //cameraTransform->addChild(touchAndGoReticule);
                touchAndGoState++;
                break;
            }
                
            case 1:
                //  Wait until stopped
                NSLog(@"Touch'N'Go State 1:  %f, %f", dx, dy);
                if ( sqrtf(dx*dx + dy*dy) < 0.06f)      //  Are we stopped?
                    touchAndGoState++;                  //  advance state                                    
                break;
                
            case 2:
                //  Rotate to face the target point
                NSLog(@"Touch'N'Go State 2");
                startFromX = spherox;
                startFromY = spheroy;
                touchAndGoDistanceToTravel = sqrtf((goToX - startFromX)*(goToX - startFromX) + (goToY - startFromY)*(goToY - startFromY));
                touchAndGoRollHeading = [self getTouchAndGoHeadingFromSpheroX:spherox Y:spheroy];
                if (touchAndGoRollHeading < 0)
                    touchAndGoRollHeading += 360;
                //  Actually send the roll command
                [RKRollCommand sendCommandWithHeading:touchAndGoRollHeading velocity:0.0f];
                
                touchAndGoRotationStartTime = time;
                touchAndGoState++;
                
                NSLog(@"Touch'N'Go distance: %f,  heading: %f", touchAndGoDistanceToTravel, touchAndGoRollHeading);
                break;
                
            case 3:
                //  Wait until the rotation has finished
                NSLog(@"Touch'N'Go State 3");
                if (time - touchAndGoRotationStartTime > 1)
                {
                    //  Record a timeout.
                    touchAndGoDriveStartTime = time;
                    //  Estimate a timeout so we know the ball will stop driving.
                    touchAndGoTimeout = sqrtf((startFromX - goToX)*(startFromX - goToX) + (startFromY - goToY)*(startFromY - goToY)) * 2.5;
                    touchAndGoState++;
                }
                break;
                
            case 4:
            {
                //  Drive to the target.
                //  How fast should we go?
                NSLog(@"Touch'N'Go State 4");
                const float velocity = [self getTouchAndGoVelocity:fabsf(touchAndGoDistanceToTravel - sqrtf((startFromX - spherox)*(startFromX - spherox) + (startFromY - spheroy)*(startFromY - spheroy)))];
                //  Recompute the heading
                //touchAndGoRollHeading = atan2f(goToY - spheroy, goToX - spherox) * 180.0f / M_PI;
                touchAndGoRollHeading = [self getTouchAndGoHeadingFromSpheroX:spherox Y:spheroy];
                if (touchAndGoRollHeading < 0)
                    touchAndGoRollHeading += 360;                
                //  Roll
                [RKRollCommand sendCommandWithHeading:touchAndGoRollHeading velocity:velocity];
                //  When sendCommandWithHeading returns 0.0f it's telling us we're there.
                if (velocity == 0.0f  ||
                    time - touchAndGoDriveStartTime > touchAndGoTimeout)
                {
                    //  We're there! (or we've given up)
                    [RKRollCommand sendStop];
                    touchAndGoIsOn = NO;        //  turn ourselves off
                    touchAndGoState = 0;        //  start state over
                    //cameraTransform->removeChild(touchAndGoReticule);
                    
                    if (time - touchAndGoDriveStartTime > touchAndGoTimeout)
                        NSLog(@"Touch'N'Go Timed Out");
                    else
                        NSLog(@"Touch'N'Go Finished");
                }
                break;
            }
        } 
        
    }

}



@end
