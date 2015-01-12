//
//  Copyright (c) 2011-2014 Orbotix Inc. All rights reserved.
//

#import "ViewController.h"
#import <RobotKit/RobotKit.h>
#import <RobotUIKit/RobotUIKit.h>
#import "OrbBasicFilesManager.h"

static NSString * const ReuseIdentifier = @"FILEPATHCELL";

@interface ViewController() <RKResponseObserver, UITableViewDataSource, UITableViewDelegate>

@property (strong, nonatomic) RKConvenienceRobot* robot;
@property (strong, nonatomic) RUICalibrateGestureHandler  *calibrateHandler;
@property (strong, nonatomic) RKOrbBasicProgram *orbBasicProgram;

@property (nonatomic, retain) IBOutlet UITableView *filesTableView;
@property (nonatomic, retain) IBOutlet UITextView *messageView;

@property (nonatomic, retain) IBOutlet UIButton *appendButton;
@property (nonatomic, retain) IBOutlet UIButton *executeButton;
@property (nonatomic, retain) IBOutlet UIButton *abortButton;
@property (nonatomic, retain) IBOutlet UIButton *eraseButton;

@end

@implementation ViewController

-(void)viewDidLoad {
    [super viewDidLoad];
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    if (![defaults objectForKey:@"firstRun"]) {
        [self copyPrebuiltPrograms];
        [defaults setObject:@(NO) forKey:@"firstRun"];
        [defaults synchronize];
    }
    
    _messageView.text = @"Loading the view.";
    self.calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
    
    [_filesTableView registerClass:[UITableViewCell class] forCellReuseIdentifier:ReuseIdentifier];
    
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
    
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(appWillResignActive:)
												 name:UIApplicationWillResignActiveNotification
											   object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
}

- (void)viewDidAppear:(BOOL)animated{
	[super viewDidAppear:animated];
	[_filesTableView reloadData];
	[_filesTableView setDelegate:self];
}

- (void)appDidBecomeActive:(NSNotification *)n {
    [RKRobotDiscoveryAgent startDiscovery];
}

- (void)appWillResignActive:(NSNotification*)n{
    [RKRobotDiscoveryAgent disconnectAll];
    [RKRobotDiscoveryAgent stopDiscovery];
}

- (void)handleRobotStateChangeNotification:(RKRobotChangedStateNotification*)n {
    switch(n.type) {
        case RKRobotConnecting:
            [self handleConnecting];
            break;
        case RKRobotOnline: {
            // Do not allow the robot to connect if the application is not running
            RKConvenienceRobot *convenience = [RKConvenienceRobot convenienceWithRobot:n.robot];
            if ([[UIApplication sharedApplication] applicationState] != UIApplicationStateActive) {
                [convenience disconnect];
                return;
            }
            self.robot = convenience;
            [self handleConnected];
            break;
        }
        case RKRobotDisconnected:
            [self handleDisconnected];
            self.robot = nil;
            [RKRobotDiscoveryAgent startDiscovery];
            break;
        case RKRobotFailedConnect:
            // edge case - handle as you will.
            break;
    }
}

- (void)handleConnecting {
    // Handle robot connecting here
}

- (void)handleConnected {
    [_calibrateHandler setRobot:_robot.robot];
    [_robot addResponseObserver:self];
    // Enable buttons
    self.appendButton.enabled = YES;
    self.executeButton.enabled = NO;
    self.abortButton.enabled = YES;
    self.eraseButton.enabled = YES;
    self.messageView.text = @"Select a program, load it to Sphero, and press to execute to run it. Press the Erase button to erase the program before loading another program.";
}

- (void)handleDisconnected {
    self.appendButton.enabled = NO;
    self.executeButton.enabled = NO;
    self.abortButton.enabled = NO;
    self.eraseButton.enabled = NO;
    [self.orbBasicProgram erase]; // This will change the state back to being unloaded.
    self.messageView.text = @"Robot disconnected.";
}

-(void)copyPrebuiltPrograms {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSError *error;
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = ([paths count] > 0) ? [paths objectAtIndex:0] : nil;
    
    //Loop through all files in the bundle resources and  copy any files that are of a managed type
    for(NSString *asset in [fileManager contentsOfDirectoryAtPath:[[NSBundle mainBundle] resourcePath] error:&error]) {
        NSString *type = [[asset componentsSeparatedByString:@"."] lastObject];
        
        if([type isEqualToString:[RKOrbBasicProgram fileExtension]]) {
            error = nil;
            NSString *assetPath = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:asset];
            NSString *destPath = [documentsDirectory stringByAppendingPathComponent:asset];
            error = nil;
            if(![fileManager copyItemAtPath:assetPath toPath:destPath error:&error]) {
                NSLog(@"AssetManager:: Error copying asset %@", asset);
                if(error) NSLog(@"AssetManager:: %@", [error localizedDescription]);
            } else {
                NSLog(@"AssetManager:: Successfully copied asset %@", asset);
            }
        }
    }
}

#pragma Actions

- (IBAction) load:(id)sender{
    [_orbBasicProgram load];
	[_orbBasicProgram setRobot:_robot.robot];
    _executeButton.enabled = YES;
}

- (IBAction)execute:(id)sender{
    _messageView.text = @"Executing ...\n";
    [_orbBasicProgram execute];
}

- (IBAction)abort:(id)sender{
    [self.orbBasicProgram abort];
}

- (IBAction)erase:(id)sender{
    [self.orbBasicProgram erase];
    self.executeButton.enabled = NO;
}

#pragma mark Message Handlers

- (void) handleResponse:(RKDeviceResponse *)response forRobot:(id<RKRobotBase>)robot{
    if ([response isKindOfClass:[RKOrbBasicAppendFragmentResponse class]]) {
        if (response.code == RKResponseCodeErrorParameter) {
            _messageView.text = [_messageView.text stringByAppendingFormat:@"Syntax error.\n"];
        } else if (response.code == RKResponseCodeErrorExecute) {
            _messageView.text = [_messageView.text stringByAppendingFormat:@"Memory full! Program not loaded.\n"];
        }
    }
}

-(void) handleAsyncMessage:(RKAsyncMessage *)message forRobot:(id<RKRobotBase>)robot{
    if ([message isKindOfClass:[RKOrbBasicPrintMessage class]]) {
        // Show print message that are generated by the program to the user.
        RKOrbBasicPrintMessage *printMessage = (RKOrbBasicPrintMessage *)message;
        _messageView.text = [_messageView.text stringByAppendingFormat:@"orbBasic Print: %@", printMessage.message];
    } else if ([message isKindOfClass:[RKOrbBasicErrorASCII class]]) {
        // Show code error messages to the user.
        RKOrbBasicErrorASCII *errorMessage = (RKOrbBasicErrorASCII *)message;
        _messageView.text = [_messageView.text stringByAppendingFormat:@"orbBasic Error: %@", errorMessage.error];
    } else if ([message isKindOfClass:[RKOrbBasicErrorBinary class]]) {
        _messageView.text = @"orbBasic binary error.";
    }
}

#pragma mark Table View Data Source Methods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return [[OrbBasicFilesManager orbBasicFiles] count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ReuseIdentifier];
    
    RKOrbBasicProgram *file = [[OrbBasicFilesManager orbBasicFiles] objectAtIndex:indexPath.row];
    cell.textLabel.text = file.name;
    
    return cell;
}

-(NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section{
	if(section == 0) return @"OrbBasic Programs";
	return @"";
}

#pragma mark Table View Delegate Methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [_orbBasicProgram erase]; // resets the state of this program so it can be reloaded.
    NSArray *programs = [OrbBasicFilesManager orbBasicFiles];
    _orbBasicProgram = [programs objectAtIndex:indexPath.row];
	[_orbBasicProgram setRobot:_robot.robot];
    self.executeButton.enabled = NO;
}

@end
