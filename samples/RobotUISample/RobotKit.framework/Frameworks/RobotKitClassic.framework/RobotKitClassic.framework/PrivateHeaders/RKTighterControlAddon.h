//
//  Copyright (c) 2013-2014 Sphero. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <RobotKitClassic/RobotKitClassic.h>

@interface RKTighterControlAddon : NSObject <RKDriveVectorAddon, RKResponseObserver>

@property ( readwrite ) BOOL enabled;
@property (strong, nonatomic) id<RKRobotBase> robot;

@end
