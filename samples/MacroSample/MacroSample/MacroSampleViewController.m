//
//  Copyright (c) 2011-2014 Orbotix, Inc. All rights reserved.
//

#import "MacroSampleViewController.h"
#import <RobotKit/RobotKit.h>

@interface MacroSampleViewController() <RKResponseObserver>

@property (nonatomic, strong) RKConvenienceRobot* robot;

@property (nonatomic,strong) IBOutlet UILabel *speedLabel;
@property (nonatomic,strong) IBOutlet UILabel *loopLabel;
@property (nonatomic,strong) IBOutlet UILabel *delayLabel;

@property (nonatomic,strong) IBOutlet UISlider *speedSlider;
@property (nonatomic,strong) IBOutlet UISlider *loopSlider;
@property (nonatomic,strong) IBOutlet UISlider *delaySlider;

@property (nonatomic, assign) BOOL ledON;
@property (nonatomic, assign) CGFloat robotSpeed;
@property (nonatomic, assign) CGFloat robotDelay;
@property (nonatomic, assign) CGFloat robotLoop;

@end

@implementation MacroSampleViewController

- (void)viewDidLoad{
    [super viewDidLoad];

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appDidBecomeActive:)
                                                 name:UIApplicationDidBecomeActiveNotification
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(appWillResignActive:)
                                                 name:UIApplicationWillResignActiveNotification
                                               object:nil];
    [self updateSliderValues];
}

-(void)appWillResignActive:(NSNotification*)notification {
    [_robot macroAbort];
    [RKRobotDiscoveryAgent disconnectAll];
    [RKRobotDiscoveryAgent stopDiscovery];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
	[RKRobotDiscoveryAgent startDiscovery];
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
        default:
            break;
    }
}

- (void)handleConnecting {
    // Handle robot connecting here
}

- (void)handleConnected {
    [_robot disableSensors];
    [_robot enableStabilization:NO];
    [_robot setBackLEDBrightness:1.0f];
    [_robot.sensorControl disableSensors];
    [_robot addResponseObserver:self];
}

- (void)handleDisconnected {
    [_robot removeResponseObserver:self];
}

//When one Slider Updates, it updates all other sliders
- (IBAction)sliderChanged:(id)sender {
    [self updateSliderValues];
}

- (void)updateSliderValues {
    //Speed Slider
    NSString *speedText=[[NSString alloc]
                         initWithFormat:@"%.f%@",(_speedSlider.value*10),@"%"];
	_speedLabel.text = speedText;
    _robotSpeed = ([speedText floatValue]* 0.1);
    
    //Delay Slider
    NSString *delayText =[[NSString alloc]
                          initWithFormat:@"%.f%@",_delaySlider.value,@" ms"];
	_delayLabel.text = delayText;
    _robotDelay = [delayText floatValue];
    
    //Loop Slider
    NSString *loopText =[[NSString alloc]
                         initWithFormat:@"%.f",_loopSlider.value];
	_loopLabel.text = loopText;
    _robotLoop = [loopText floatValue];
    
}

//Macros
//Abort Macros
- (IBAction)AbortMacro:(id)sender {
    [_robot macroAbort];
    [_robot enableStabilization:YES];
    [_robot stop];
    [_robot setLEDWithRed:1.0f green:1.0f blue:1.0f];
}

//Simple Square, no repeat
- (IBAction)MacroSquare:(id)sender {
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Change Color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:0 delay:_robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to blue
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:0]];
    //Sphero drives forward in the 90 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:90 delay:_robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to yellow
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 180 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:180 delay:_robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to red
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:0.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 270 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:270 delay:_robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to white
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:1.0 delay:0]];
    //Sphero comes to stop in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:3000]];
    //Send full command dowm to Sphero to play
	
	RKMacroPlayer *player = [[RKMacroPlayer alloc] initWithRobot:_robot.robot];
	[player play:macro];
}

//Colors Fade during action (Circle)
//Slew(Fade) is a parrelell command
//When Slew action is performed, either have it run parrallel to a roll command or a delay.
//If the user was to include a blink color it would then end the slew abrutly.
- (IBAction)MacroColor:(id)sender {
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Sets loop from slider value
    [macro addCommand:[RKMCLoopFor commandWithRepeats:_robotLoop]];
    //Fade color to Blue
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:0.0 blue:1.0 delay:_robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:_robotDelay]];
    //Fade color to Red
    [macro addCommand:[RKMCSlew commandWithRed:1.0 green:0.0 blue:0.0 delay:_robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:_robotDelay]];
    //Fade color to Green
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:1.0 blue:0.0 delay:_robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:_robotDelay]];
    //Loop End
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
	RKMacroPlayer *player = [[RKMacroPlayer alloc] initWithRobot:_robot.robot];
	[player play:macro];
}

//Macro Shape
//Changes the Shape depending on the number of loops you include
//Example: 4 loops makes a square
//360 degrees / (4)= 90 degree turns
- (IBAction)MacroShape:(id)sender {
     //Create a new macro object to send to Sphero
     RKMacroObject *macro = [RKMacroObject new];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:_robotLoop]];
    //Change color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:1000]];
    
    // Adding sequence of macro commands to make a full shape with
    // number of sides equal to robotLoop
    for(int i = 0; i < _robotLoop; i++) {
        //Come to Stop
        [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:100]];
        [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:i*(360/_robotLoop) delay:_robotDelay]];
    }
    
    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
	RKMacroPlayer *player = [[RKMacroPlayer alloc] initWithRobot:_robot.robot];
	[player play:macro];
}

//Figure 8 repeat
//RotateOverTime is a parallel command
//When a rotation action is performed, either have it run parallel to a color command or a delay.
//If the user was to include a drive command it would then end the rotation abrumtly.
- (IBAction)MacroFigureEight:(id)sender {
    //Start with verb!!
    //Give Loop
    
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Tell Robot to look forward and to start driving
    [macro addCommand:[RKMCRoll commandWithSpeed:_robotSpeed heading:0 delay:2000]];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:_robotLoop]];
    ///Tell Robot to perform 1st turn in the postive direction.
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:360 delay:_robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:_robotDelay]];
    //Rotate to pertform the 2nd turn in the negitive direction
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:-360 delay:_robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:_robotDelay]];
    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Come to stop
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:1000]];
    //Send full command dowm to Sphero to play
	RKMacroPlayer *player = [[RKMacroPlayer alloc] initWithRobot:_robot.robot];
	[player play:macro];
}

@end
