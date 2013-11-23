//
//  RKMultiplayerGame.h
//  RobotKit
//
//  Created by Jon Carroll on 8/9/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//
//  Description: Represents an available multiplayer game
//  Returned by RKMultiplayer delegate methods when requesting
//  the list of available games.

#import <Foundation/Foundation.h>

@interface RKMultiplayerGame : NSObject {
    NSNetService *service;
}

@property (nonatomic, retain) NSNetService *service;

/*!
 *  Returns a name to display to represent the game
 */
-(NSString*)name;

@end
