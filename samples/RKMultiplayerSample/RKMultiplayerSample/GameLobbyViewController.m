//
//  GameLobbyViewController.m
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//

#import "GameLobbyViewController.h"

@interface GameLobbyViewController ()

@end

@implementation GameLobbyViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
        self.hidesBottomBarWhenPushed = YES;
        self.title = @"Lobby";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    players = [RKMultiplayer sharedMultiplayer].remotePlayers;
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
    //Set this view controller as the multiplayer delegate so it gets callbacks
    [RKMultiplayer sharedMultiplayer].delegate = self;
}

-(void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self updateButtonUIForState];
    [self updatePlayerList];
}

-(void)viewWillDisappear:(BOOL)animated {
    [UIApplication sharedApplication].idleTimerDisabled = NO;
    [super viewWillDisappear:animated];
    [[RKMultiplayer sharedMultiplayer] endGame];
}

#pragma mark -
#pragma mark UI Updating for state changes

-(void)updateButtonUIForState {
    RKMultiplayerGameState state = [RKMultiplayer sharedMultiplayer].gameState;
    if(state==RKMultiplayerGameStateLobby) {
        if([RKMultiplayer sharedMultiplayer].isHost) {
            startButton.enabled = YES;
            startButton.alpha = 1.0;
        } else {
            startButton.enabled = NO;
            startButton.alpha = 0.25;
        }
        endButton.enabled = NO;
        endButton.alpha = 0.25;
        pauseButton.enabled = NO;
        pauseButton.alpha = 0.25;
        resumeButton.enabled = NO;
        resumeButton.alpha = 0.25;
        stateLabel.text = @"GameState: Lobby";
    } else if(state==RKMultiplayerGameStateStarted) {
        startButton.enabled = NO;
        startButton.alpha = 0.25;
        if([RKMultiplayer sharedMultiplayer].isHost) {
            endButton.enabled = YES;
            endButton.alpha = 1.0;
        } else {
            endButton.enabled = NO;
            endButton.alpha = 0.25;
        }
        pauseButton.enabled = YES;
        pauseButton.alpha = 1.0;
        resumeButton.enabled = NO;
        resumeButton.alpha = 0.25;
        stateLabel.text = @"GameState: Started";
    } else if(state==RKMultiplayerGameStatePaused) {
        startButton.enabled = NO;
        startButton.alpha = 0.25;
        if([RKMultiplayer sharedMultiplayer].isHost) {
            endButton.enabled = YES;
            endButton.alpha = 1.0;
        } else {
            endButton.enabled = NO;
            endButton.alpha = 0.25;
        }
        pauseButton.enabled = NO;
        pauseButton.alpha = 0.25;
        resumeButton.enabled = YES;
        resumeButton.alpha = 1.0;
        stateLabel.text = @"GameState: Paused";
    } else if(state==RKMultiplayerGameStateEnded) {
        startButton.enabled = NO;
        startButton.alpha = 0.25;
        endButton.enabled = NO;
        endButton.alpha = 0.25;
        pauseButton.enabled = NO;
        pauseButton.alpha = 0.25;
        resumeButton.enabled = NO;
        resumeButton.alpha = 0.25;
        stateLabel.text = @"GameState: Ended";
    }
}

-(void)updatePlayerList {
    NSString *playerListText = @"";
    for(RKRemotePlayer *player in players) {
        if(player.host) {
            playerListText = [playerListText stringByAppendingString:@"*"];
        }
        playerListText = [playerListText stringByAppendingFormat:@"%@ - %1.0f ms\n", player.name, player.latency];
    }
    playersList.text = playerListText;
}

#pragma mark -
#pragma mark UI Interaction

-(IBAction)startPressed:(id)sender {
    [[RKMultiplayer sharedMultiplayer] startGame];
}

-(IBAction)endPressed:(id)sender {
    [[RKMultiplayer sharedMultiplayer] endGame];
}

-(IBAction)pausePressed:(id)sender {
    [[RKMultiplayer sharedMultiplayer] pauseGame];
}

-(IBAction)resumePressed:(id)sender {
    [[RKMultiplayer sharedMultiplayer] resumeGame];
}

-(IBAction)sendPressed:(id)sender {
    [chatField resignFirstResponder];
    if(chatField.text==nil || [chatField.text isEqualToString:@""]) {
        return;
    }
    NSMutableDictionary *payload = [[NSMutableDictionary alloc] init];
    [payload setObject:chatField.text forKey:@"CHAT"];
    [[RKMultiplayer sharedMultiplayer] sendDataToAll:payload];
    [payload release];
    
    chatList.text = [chatList.text stringByAppendingFormat:@"\n%@: %@", [RKMultiplayer sharedMultiplayer].localPlayer.name, chatField.text];
    [chatList setContentOffset:CGPointMake(0, chatList.contentSize.height - chatList.frame.size.height + 20) animated:YES];
    
    chatField.text = @"";
}

#pragma mark -
#pragma mark UITextField delegate

- (void)textFieldDidBeginEditing:(UITextField *)textField {
    self.view.transform = CGAffineTransformTranslate(self.view.transform, 0.0, -220);
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
    self.view.transform = CGAffineTransformTranslate(self.view.transform, 0.0, 220);
}

#pragma mark -
#pragma mark RKMultiplayer Delegate Methods

-(void)multiplayerPlayerDidJoinGame:(RKRemotePlayer*)player {
    [self updatePlayerList];
}

-(void)multiplayerPlayerDidLeaveGame:(RKRemotePlayer*)player {
    [self updatePlayerList];
}

-(void)multiplayerPlayerInformationDidUpdate:(RKRemotePlayer *)player {
    [self updatePlayerList];
}

-(void)multiplayerPlayerOrderDidChange {
    [self updatePlayerList];
}

-(void)multiplayerGameStateDidChangeToState:(RKMultiplayerGameState)newState {
    [self updateButtonUIForState];
}

-(void)multiplayerDidRecieveData:(NSDictionary*)data fromPlayer:(RKRemotePlayer*)player {
    [self updatePlayerList];
    chatList.text = [chatList.text stringByAppendingFormat:@"\n%@: %@", player.name, [data objectForKey:@"CHAT"]];
    [chatList setContentOffset:CGPointMake(0, chatList.contentSize.height - chatList.frame.size.height + 20) animated:YES];
}

@end
