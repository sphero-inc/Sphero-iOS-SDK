//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol RKDriveable <NSObject>

-(void) calibrating:(BOOL) yn;

-(void) driveWithHeading:(float) heading andVelocity:(float) velocity;

-(void) rotateWithHeading:(float) heading;

-(void) stop;

@end
