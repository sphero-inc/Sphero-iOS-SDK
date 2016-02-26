//
//  RKRobotFavorites.h
//  RobotKitLE
//
//  Created by wes on 9/11/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "RKRobotLE.h"

@interface RKLeFavoritesManager : NSObject

@property (strong, nonatomic, readonly) NSMutableSet *favoriteRobotUUIDS; // NSUUID

+(RKLeFavoritesManager *) sharedManager;

-(void) addRobotToFavorites:(RKRobotLE*) robot;
-(void) removeRobotFromFavorites:(RKRobotLE*) robot;
-(bool) isRobotAFavorite:(RKRobotLE*) robot;
-(void) clearRobotFavorites;

@end
