//
//  RKNonPersistentOptionsFlagResponse.h
//  RobotKit
//
//  Created by wes felteau on 4/16/13.
//  Copyright (c) 2013 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <RobotKit/RobotKit.h>

typedef NS_ENUM(uint32_t, RKNonPersistentOptionsFlagMask){
    StopOnDisconnect = 0x00000001
};


/*! */
@interface RKNonPersistentOptionsFlagResponse : RKDeviceResponse

/*! The current option flags on the device */
@property ( nonatomic, readonly ) RKNonPersistentOptionsFlagMask mask;

/*! */
- (BOOL) isStopOnDisconnect;

@end
