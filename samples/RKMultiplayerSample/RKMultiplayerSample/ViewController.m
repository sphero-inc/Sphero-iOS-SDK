//
//  ViewController.m
//  RKMultiplayerSample
//
//  Created by Jon Carroll on 4/12/12.
//  Copyright (c) 2012 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"

#import "RobotKit/RobotKit.h"

#import "RobotUIKit/RobotUIKit.h"

#import "GameLobbyViewController.h"

#import "NameEntryViewController.h"

@implementation ViewController

@synthesize games;

-(void)viewDidLoad {
    [super viewDidLoad];
    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
    
    self.title = @"Games";
    
    //Setup toolbar buttons
    UIBarButtonItem *addItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd target:self action:@selector(createGame)];
    UIBarButtonItem *flexibleSpace = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace target:nil action:nil];
    UIBarButtonItem *nameButton = [[UIBarButtonItem alloc] initWithTitle:@"Set Name" style:UIBarButtonItemStyleBordered target:self action:@selector(setName)];
    NSArray *items = [NSArray arrayWithObjects:nameButton, flexibleSpace, addItem, nil];
    self.toolbarItems = items;
    [addItem release];
    [flexibleSpace release];
    [nameButton release];
    
    

    calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
}

-(void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    
    self.games = nil;
    
    [self.tableView reloadData];
    //Start getting available multiplayer games when this view appears.
    [RKMultiplayer sharedMultiplayer].delegate = self;
    [[RKMultiplayer sharedMultiplayer] getAvailableMultiplayerGamesOfType:@"MPSample"];
    
}

-(void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    //Stop getting available multiplayer games when the view disappears
    [[RKMultiplayer sharedMultiplayer] stopGettingAvailableMultiplayerGames];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

-(void)appWillResignActive:(NSNotification*)notification {
    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
        /*Only start the blinking loop once*/
        [self toggleLED];
    }
    robotOnline = YES;
}

- (void)toggleLED {
    /*Toggle the LED on and off*/
    if (ledON) {
        ledON = NO;
        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];
    } else {
        ledON = YES;
        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:1.0];
    }
    [self performSelector:@selector(toggleLED) withObject:nil afterDelay:0.5];
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
    }
}

#pragma mark -
#pragma mark UI interaction

-(void)createGame {
    [[RKMultiplayer sharedMultiplayer] stopGettingAvailableMultiplayerGames];
    GameLobbyViewController *lobby = [[GameLobbyViewController alloc] initWithNibName:@"GameLobbyViewController" bundle:nil];
    [self.navigationController pushViewController:lobby animated:YES];
    [lobby release];
    [[RKMultiplayer sharedMultiplayer] hostGameOfType:@"MPSample" playerName:[RKMultiplayer sharedMultiplayer].localPlayer.name];
}

-(void)setName {
    NameEntryViewController *controller = [[NameEntryViewController alloc] initWithNibName:@"NameEntryViewController" bundle:nil];
    [self.navigationController pushViewController:controller animated:YES];
    [controller release];
}

#pragma mark -
#pragma mark RKMultiplayer Delegate Methods

-(void)multiplayerDidUpdateAvailableGames:(NSArray*)gamearray {
    self.games = gamearray;
    [self.tableView reloadData];
}

#pragma mark -
#pragma mark Table View delegate methods

//Table view delegate calls for listing the available games

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [games count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *identifier = @"cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if(cell==nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:identifier] autorelease];
    }
    
    RKMultiplayerGame *game = [games objectAtIndex:indexPath.row];
    cell.textLabel.text = [game name];
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    RKMultiplayerGame *game = [games objectAtIndex:indexPath.row];
    [[RKMultiplayer sharedMultiplayer] joinAdvertisedGame:game];
    [[RKMultiplayer sharedMultiplayer] stopGettingAvailableMultiplayerGames];
    GameLobbyViewController *lobby = [[GameLobbyViewController alloc] initWithNibName:@"GameLobbyViewController" bundle:nil];
    [RKMultiplayer sharedMultiplayer].delegate = lobby;
    [self.navigationController pushViewController:lobby animated:YES];
    [lobby release];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];

    
}

@end
