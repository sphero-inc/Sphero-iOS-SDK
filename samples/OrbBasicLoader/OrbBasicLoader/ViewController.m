//
//  ViewController.m
//  OrbBasicLoader
//
//  Created by Brian Smith on 10/1/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"

#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>

#import "OrbBasicFilesManager.h"


@implementation ViewController

@synthesize filesTableView;
@synthesize messageView;

@synthesize appendButton;
@synthesize executeButton;
@synthesize abortButton;
@synthesize eraseButton;


-(void)viewDidLoad {
    [super viewDidLoad];
    
    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
    connectionSetupFinished = NO;
    messageView.text = @"Loading the view.";
    
    calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    // Make sure the available OrbBasicPrograms show up in the table view.
    [filesTableView reloadData];
}

-(void)appWillResignActive:(NSNotification*)notification {
    /* When the application is entering the background we need to close the connection to the robot */
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:RKDeviceConnectionOnlineNotification
                                                  object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:RKDeviceConnectionOfflineNotification
                                                  object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:RKRobotDidLossControlNotification
                                                  object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:RKRobotDidGainControlNotification
                                                  object:nil];

    // Stop observing responses and asynchronous data from Sphero.
    [[RKDeviceMessenger sharedMessenger] removeDataStreamingObserver:self];
    [[RKDeviceMessenger sharedMessenger] removeResponseObserver:self];
    
    // Stop communication with Sphero.
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
    robotOnline = NO;
    connectionSetupFinished = NO;
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /* When the application becomes active after entering the background we try to connect to the robot */
    [self setupRobotConnection];
}

- (void)handleRobotOnline {
    /* The robot is now online, we can begin sending commands */
    if (robotOnline) return;
    
    // Set observer methods to handle messages from Sphero.
    [[RKDeviceMessenger sharedMessenger] addResponseObserver:self selector:@selector(handleResponse:)];
    [[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self selector:@selector(handleAsyncData:)];
    
    // Enable buttons
    self.appendButton.enabled = YES;
    self.executeButton.enabled = NO;
    self.abortButton.enabled = YES;
    self.eraseButton.enabled = YES;
    
    robotOnline = YES;
    
    messageView.text = @"Select a program, load it to Sphero, and press to execute to run it. Press the Erase button to erase the program before loading another program.";
}

- (void)handleRobotOffline
{
    messageView.text = @"Sphero is not responding. Make sure it is connected and turned on.";
}

- (void)handleRobotDidLoseControl:(NSNotification *)notification
{
    // Sphero disconnected for some reason.
    //// disable buttons
    appendButton.enabled = NO;
    executeButton.enabled = NO;
    abortButton.enabled = NO;
    eraseButton.enabled = NO;
    
    [orbBasicProgram erase]; // This will change the state back to being unloaded.
    
    messageView.text = @"Sphero disconnected.";

    robotOnline = NO;
}

- (void)handleRobotDidGainControl:(NSNotification *)notification
{
    // Make sure that we a reconnecting while the application is running instead of
    // connecting from application start.
    if (!connectionSetupFinished) return;
    
    // reconnect to Sphero
    [[RKRobotProvider sharedRobotProvider] openRobotConnection];
    messageView.text = @"Sphero reconnected. Setting up connection to Sphero....";
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleRobotOnline)
                                                 name:RKDeviceConnectionOnlineNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleRobotOffline)
                                                 name:RKDeviceConnectionOfflineNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleRobotDidLoseControl:)
                                                 name:RKRobotDidLossControlNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleRobotDidGainControl:)
                                                 name:RKRobotDidGainControlNotification
                                               object:nil];

    if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) {
        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
        messageView.text = @"Setting up connection to Sphero....";
    } else {
        messageView.text = @"Sphero is not connected. Make sure it is turned on.";
    }
    
    connectionSetupFinished = YES;
}

#pragma Actions

- (void)load:(id)sender
{
    // Send the program to Sphero. This will erase the previous loaded program.
    [orbBasicProgram load];
    self.executeButton.enabled = YES;
}

- (void)execute:(id)sender
{
    // Execute the program. This will load the program if it is not already loaded.
    messageView.text = @"Executing ...\n";
    [orbBasicProgram execute];
}

- (void)abort:(id)sender
{
    // Aborts the current program.
    [orbBasicProgram abort];
}

- (void)erase:(id)sender
{
    // Erases the current program.
    [orbBasicProgram erase];
    self.executeButton.enabled = NO;
}


#pragma mark Message Handlers

- (void)handleResponse:(RKDeviceResponse *)response
{
    if ([response isKindOfClass:[RKOrbBasicAppendFragmentResponse class]]) {
        if (response.code == RKResponseCodeErrorParameter) {
            messageView.text = [messageView.text stringByAppendingFormat:@"Syntax error.\n"];
        } else if (response.code == RKResponseCodeErrorExecute) {
            messageView.text = [messageView.text stringByAppendingFormat:@"Memory full! Program not loaded.\n"];
        }
    }
}

- (void)handleAsyncData:(RKDeviceAsyncData *)data
{
    if ([data isKindOfClass:[RKOrbBasicPrintMessage class]]) {
        // Show print message that are generated by the program to the user.
        RKOrbBasicPrintMessage *printMessage = (RKOrbBasicPrintMessage *)data;
        messageView.text = [messageView.text stringByAppendingFormat:@"orbBasic Print: %@", printMessage.message];
    } else if ([data isKindOfClass:[RKOrbBasicErrorASCII class]]) {
        // Show code error messages to the user.
        RKOrbBasicErrorASCII *errorMessage = (RKOrbBasicErrorASCII *)data;
        messageView.text = [messageView.text stringByAppendingFormat:@"orbBasic Error: %@", errorMessage.error];
    } else if ([data isKindOfClass:[RKOrbBasicErrorBinary class]]) {
        messageView.text = @"orbBasic binary error.";
    }
}


#pragma mark Table View Data Source Methods


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[OrbBasicFilesManager orbBasicFiles] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString * const ReuseIdentifier = @"FILEPATHCELL";
    
    // Create a basic cell and add the file path to it.
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ReuseIdentifier];
    if ( cell == nil ) {
         cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:ReuseIdentifier];
    }
    
    RKOrbBasicProgram *file = [[OrbBasicFilesManager orbBasicFiles] objectAtIndex:indexPath.row];
    cell.textLabel.text = file.name;
    
    return [cell autorelease];
}

#pragma mark Table View Delegate Methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [orbBasicProgram erase]; // resets the state of this program so it can be reloaded.
    NSArray *programs = [OrbBasicFilesManager orbBasicFiles];
    orbBasicProgram = [programs objectAtIndex:indexPath.row];
    self.executeButton.enabled = NO;
}

@end
