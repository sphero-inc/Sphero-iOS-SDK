//
//  RKMultiplayer.h
//  RobotKit
//
//  Created by Jon Carroll on 8/8/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//
//  Description: Layer 3 in the RKMultiplayer stack.
//  Handles session management, joining, other players
//  and passing data to the application layer.
//  This is a singleton, don't create your own

#import <Foundation/Foundation.h>
#include <CFNetwork/CFNetwork.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

@class RKMultiplayerDataJSON;
@class RKMultiplayerNetworkWIFI;
@class RKRemotePlayer;
@class RKMultiplayerGame;
@protocol RKMultiplayerDelegateProtocol;

typedef enum RKMultiplayerGameState {
    RKMultiplayerGameStateLobby, //Players can join
    RKMultiplayerGameStateStarted, //Game in progress
    RKMultiplayerGameStateEnded, //Game ended
    RKMultiplayerGameStatePaused
} RKMultiplayerGameState;


/*!
 *  @brief RKMultiplayer is a signleton manager that handles multiplayer games
 *
 *  This class will discover, advertise, connect to and manage multiplayer games.
 *  Also supports remote control of robots connected to other clients.
 *  TCP connections are used for communication and in order delivery is guarunteed.
 *  A hub and spoke network is created with host at the center, if host leaves game is toast.
 *  Currently if any player leaves the game state will transition to RKMultiplayerGameStateEnded
 *  It is a singleton class and should not be allocated.
 *
 *  See Also:
 *  @sa RKRemotePlayer
 *  @sa RKRemoteRobot
 *  @sa RKMultiplayerGame
 */
@interface RKMultiplayer : NSObject <NSNetServiceDelegate, NSNetServiceBrowserDelegate> {
    RKMultiplayerDataJSON       *dataLayer;
    id                          delegate;
    NSNetService                *gameAdvertiser;
    NSNetServiceBrowser         *gameBrowser;
    BOOL                        isHost;
    NSMutableArray              *games;
    NSString                    *localUID;
    NSString                    *localName;
    RKRemotePlayer              *localPlayer;
    BOOL                        haveRobot;
    RKMultiplayerGameState      gameState;
    NSString                    *gameType;
    NSString                    *gameName;
    
    
    CFSocketRef                 listeningSocket;
    NSInputStream*              networkStream;
    
    NSMutableArray              *remotePlayers;
    RKMultiplayerGame           *currentGame;
}

/*! The delegate that will recieve multiplayer delegate messages */
@property (nonatomic, assign) id <RKMultiplayerDelegateProtocol>    delegate;

/*! YES if the local player is the host, NO otherwise */
@property (readonly)          BOOL                                  isHost;

/*! Array of RKRemotePlayer objects representing all the players in the game (including the local player) */
@property (nonatomic, retain) NSMutableArray                        *remotePlayers;

/*! The RKRemotePlayer object representing the local player.  Can also be found in remotePlayers array */
@property (nonatomic, retain, readonly) RKRemotePlayer              *localPlayer;

/*! Manual control over whether the local player advertises it's connected robot, set to NO to not advertise local robot even if there is one */
@property BOOL                                                      haveRobot;

/*! The current game state */
@property (nonatomic, readonly) RKMultiplayerGameState              gameState;

/*! Call to get the shared singleton.  
 *  You can try to create an instance but the init method will also return the singleton.
 *  @return The RKMultiplayer singleton instance
 */
+(RKMultiplayer*)sharedMultiplayer;

/*! Call to start advertising that you are hosting a game. Will start accepting incoming connections.
 *  @param gameType The type used to broadcast the game as a service on the network.
 *  @param playerName should be unique but human readable, will be
 *  displayed in game list, preferably SW username or ball
 *  name. 
 */
- (void)hostGameOfType:(NSString* )gameType playerName:(NSString *)playerName;

/*! Call to stop hosting the game and remove other players
 *  from the session.  Might be called when host backs out
 *  of lobby
 */
-(void)stopHostingGame;

/*! Remove the given player from the game.
 */
-(void)removePlayerFromGame:(RKRemotePlayer*)playerToRemove;

/*! Kick the player to see if they're still connected.  If we
 *  don't get a response the player will be disconnected.
 */
-(void)kickPlayer:(RKRemotePlayer*)player;

/*! Call to have a client join a host's game 
 *  @sa RKMultiplayerGame
 */
-(void)joinAdvertisedGame:(RKMultiplayerGame*)game;

/*! Call to leave current game as a client or host
 */
-(void)leaveCurrentGame;

/*! Call to get list of multiplayer games, returns immediately, 
 *  games returned in delegate callback as they are discovered.
 *  @param gameType The type used by hosts to broadcast the game service on
 *  the network.
 */
-(void)getAvailableMultiplayerGamesOfType:(NSString *)gameType;

/*! Call to stop getting the available multiplayer games callbacks
 *  Called automatically when joining or hosting a game
 *  Would need to be called manually if user backs out of multiplayer
 *  game list for example.
 */
-(void)stopGettingAvailableMultiplayerGames;

/*! Send data to all players in the game
 *  @param data dictionary of data to send to all other players
 */
-(void)sendDataToAll:(NSDictionary*)data;

/*! Send data to a particular player
 *  @param data dictionary of data to send to the player
 *  @param player RKRemotePlayer to send the data to
 *  @sa RKRemotePlayer
 */
-(void)sendData:(NSDictionary*)data toPlayer:(RKRemotePlayer*)player;

/*! Internal method
 */
-(void)recievedData:(NSDictionary*)data fromPlayer:(RKRemotePlayer*)player;

/*! Should be called by the host to start the game
 *  Will transition game state from lobby to started
 *  Will stop advertising game, players no longer able to join
 */
-(void)startGame;

/*! Call to manually transition the game state to ended
 *  This automatically call leave current game if not the host
 *  If called from the host it will close all connections and
 *  end the game for all players.
 */
-(void)endGame;

/*! Call this to return the game state to the lobby if this device is host.
 *  This will cause all other player's game states to return to lobby.
 *  The host will begin advertising the game again and players will be able
 *  to join the game.
 */
-(void)returnToLobby;

/*!
 *  Call to cause the game to transition to the pause state for all players
 */
-(void)pauseGame;

/*!
 *  Call to cause the game to transition back to the play state if paused
 */
-(void)resumeGame;

/*!
 *  Generates a timestamp that can be sent in payload and converted to
 *  local time on a remote device using RKRemotePlayer time syncing.
 *  The value returned is ms since the unix epoch.
 */
+(NSNumber*)currentTimestamp;

/*!
 *  Enables multiplayer debug output, all messages and state changes are logged
 *  The default is NO.  This can be helpful when debugging, should be turned
 *  off for release.
 */
+(void)setMultiplayerDebug:(BOOL)setting;

@end



@protocol RKMultiplayerDelegateProtocol
@optional
/*! Called when the available list of multiplayer games has updated
 *  array contains RKMultiplayerGame objects representing available games
 *  @param games Array of RKMultiplayerGame objects representing available multiplayer games in lobby state
 *  @sa RKMultiplayerGame
 */
-(void)multiplayerDidUpdateAvailableGames:(NSArray*)games;

/*! Sent to all clients in a game when another joins for updating UI
 *  @param player RKRemotePlayer instance representing the player that just joined
 *  @sa RKRemotePlayer
 */
-(void)multiplayerPlayerDidJoinGame:(RKRemotePlayer*)player;

/*! Sent to all clients in a game when another player leaves for updating UI
 *  @param player RKRemotePlayer instance representing the player that just left
 *  @sa RKRemotePlayer
 */
-(void)multiplayerPlayerDidLeaveGame:(RKRemotePlayer*)player;

/*! Called when information about a player is updated such as their name or latency
 *  @param player The player that had their information updated.
 */
-(void)multiplayerPlayerInformationDidUpdate:(RKRemotePlayer*)player;

/*! Sent to client when sort order of clients has changed, order of remotePlayers
 *  array will have already changed when this call fires. UI should be updated
 *  this call should only fire during the lobby state
 */
-(void)multiplayerPlayerOrderDidChange;

/*! Sent on game state change for updating UI
 *  @param newState RKMultiplayerGameState representing the new game state.
 */
-(void)multiplayerGameStateDidChangeToState:(RKMultiplayerGameState)newState;

/*! Called when data is recieved from another player
 *  @param data This is the payload the other player sent with headers removed
 *  @param player The remote player the data was recieved from
 */
-(void)multiplayerDidRecieveData:(NSDictionary*)data fromPlayer:(RKRemotePlayer*)player;

/*! DEPRECATED: This callback is deprecated, please use the call above instead
 *  Called when data is recieved from another player.
 *  @param data Dictionary with data that was sent, sent data is under key @"PAYLOAD"
 */
-(void)multiplayerDidRecieveGameData:(NSDictionary*)data __attribute__((deprecated));

@end


