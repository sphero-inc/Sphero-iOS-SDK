//
//  RKLogarithmicScaleModifier.h
//  RobotKit
//
//  Created by wes felteau on 3/25/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKit/RobotKit.h>

@interface RKLogarithmicScaleDriveAddon : NSObject <RKDriveVectorAddon>

@property ( readwrite ) BOOL enabled;
@property ( readwrite ) float logScale;

- (id) initWithScale:(float) inLogScale;

@end
