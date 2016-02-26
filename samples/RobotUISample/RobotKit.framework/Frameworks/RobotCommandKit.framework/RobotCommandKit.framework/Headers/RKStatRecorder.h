//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKStat.h"

@interface RKStatRecorder : NSObject

+ (RKStatRecorder *)sharedRecorder;
- (void)recordStat:(RKStat *)stat;
- (void)forceSync;

@end
