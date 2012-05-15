//
//  GameLobbyViewController.h
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//
//  View controller that shows the players in the game and presents a chat room

#import <UIKit/UIKit.h>
#import <RobotKit/RobotKit.h>

@interface GameLobbyViewController : UIViewController <RKMultiplayerDelegateProtocol, UITextFieldDelegate> {
    NSMutableArray *players;
    IBOutlet UILabel *stateLabel;
    IBOutlet UIButton *startButton, *endButton, *pauseButton, *resumeButton, *lobbyButton;
    IBOutlet UIButton *sendButton;
    IBOutlet UITextView *playersList, *chatList;
    IBOutlet UITextField *chatField;
}

-(IBAction)startPressed:(id)sender;
-(IBAction)endPressed:(id)sender;
-(IBAction)pausePressed:(id)sender;
-(IBAction)resumePressed:(id)sender;
-(IBAction)sendPressed:(id)sender;
-(IBAction)lobbyPressed:(id)sender;

-(void)updateButtonUIForState;
-(void)updatePlayerList;

@end
