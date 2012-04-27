//
//  MainViewController.h
//  TwoPhonesOneBall
//
//  Created by Jon Carroll on 8/12/11.
//  Copyright 2011 Orbotix, Inc. All rights reserved.
//

#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import <RobotKit/RKMultiplayer.h>

@class RKRemotePlayer;

@interface MainViewController : UIViewController <RUIColorPickerDelegate, RKMultiplayerDelegateProtocol> {
    IBOutlet UISlider   *speedSlider;
    IBOutlet UISlider   *headingSlider;
    IBOutlet UIButton   *passButton;
    IBOutlet UILabel    *connectionMessage;
    RKRemotePlayer      *remotePlayer;//RKMultiplayer class representing the remote player and their robot
    float               heading; //Need to keep track of this in an ivar for RCDrive controls
    float               lastSpeed;
    float               lastHeading;
}

-(IBAction)passPressed;
-(IBAction)sliderTouchUp:(id)sender; //When a finger is lifted up on a slider we want to move it back to 0
-(void)controlLoop;

//Called when the available list of multiplayer games has updated
//array contains RKMultiplayerGame objects representing available games
-(void)multiplayerDidUpdateAvailableGames:(NSArray*)games;

//Sent to all clients in a game when another joins for updating UI
-(void)multiplayerPlayerDidJoinGame:(RKRemotePlayer*)player;

//Sent to all clients in a game when another player leaves for updating UI
-(void)multiplayerPlayerDidLeaveGame:(RKRemotePlayer*)player;

//Sent on game state change for updating UI
-(void)multiplayerGameStateDidChangeToState:(RKMultiplayerGameState)newState;

//Called when game data is recieved from another player
-(void)multiplayerDidRecieveGameData:(NSDictionary*)data;


@end
