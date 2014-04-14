//
//  ViewController.m
//  HelloWorld
//
//  Created by Jon Carroll on 12/8/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"
#import "RobotKit/RobotKit.h"
#import "RobotKit/RKMacroObject.h"
#import "RobotKit/RKAbortMacroCommand.h"
@implementation ViewController

@synthesize loopLabel;
@synthesize speedLabel;
@synthesize delayLabel;

@synthesize loopSlider;
@synthesize speedSlider;
@synthesize delaySlider;


#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.

    /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillTerminate:) name:UIApplicationWillTerminateNotification object:nil];

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;
    
    [self updateSliderValues];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

-(void)appWillTerminate:(NSNotification*)notification {

    /*When the application is entering the background we need to close the connection to the robot*/
    [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
    [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:1.0 blue:1.0];
    //Abort Command
    [RKAbortMacroCommand sendCommand];
    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
}

-(void)appDidBecomeActive:(NSNotification*)notification {
    /*When the application becomes active after entering the background we try to connect to the robot*/
    [self setupRobotConnection];
}

#pragma mark-Sphero Connection
- (void)handleRobotOnline {
    /*The robot is now online, we can begin sending commands*/
    if(!robotOnline) {
        // Robot Initializationg State Code Goes Here
    }
    robotOnline = YES;
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];
    [[RKRobotProvider sharedRobotProvider] openRobotConnection];        
}

#pragma mark-Sliders
//When one Slider Updates, it updates all other sliders
-(IBAction) sliderChanged:(id) sender{
    [self updateSliderValues];
}

-(void)updateSliderValues {
    //Speed Slider
    NSString *speedText=[[NSString alloc]
                         initWithFormat:@"%.f%@",(speedSlider.value*10),@"%"];
	speedLabel.text = speedText;
    robotSpeed = ([speedText floatValue]* 0.1);
    
    //Delay Slider
    NSString *delayText =[[NSString alloc]
                          initWithFormat:@"%.f%@",delaySlider.value,@" ms"];
	delayLabel.text = delayText;
    robotDelay = [delayText floatValue];
    
    //Loop Slider
    NSString *loopText =[[NSString alloc]
                         initWithFormat:@"%.f",loopSlider.value];
	loopLabel.text = loopText;
    robotLoop = [loopText floatValue];
    
    [loopText release];
    [speedText release];
    [delayText release];
}

#pragma mark-Macros
//Macros
//Abort Macros
-(IBAction)AbortMacro:(id)sender{
    //Abort Command
    [RKAbortMacroCommand sendCommand];
    //Turn on Stabilization
    [RKStabilizationCommand sendCommandWithState:(RKStabilizationStateOn)];
    //Send Roll Stop
    [RKRollCommand sendStop];
    //Change heading back to 0
    [RKRollCommand sendCommandWithHeading:0 velocity:0.0];
    [RKRGBLEDOutputCommand sendCommandWithRed:255 green:255 blue:255];
    //[RKRobotProvider sharedRobotProvider].robot.
}

//Simple Square, no repeat
-(IBAction)MacroSquare:(id)sender{
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Change Color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:0 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to blue
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:0]];
    //Sphero drives forward in the 90 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:90 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to yellow
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 180 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:180 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to red
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:0.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 270 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:270 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to white
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:1.0 delay:0]];
    //Sphero comes to stop in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:3000]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];
}

//Colors Fade during action (Circle)
//Slew(Fade) is a parrelell command
//When Slew action is performed, either have it run parrallel to a roll command or a delay.
//If the user was to include a blink color it would then end the slew abrutly.
-(IBAction)MacroColor:(id)sender{
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Sets loop from slider value
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    //Fade color to Blue
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:0.0 blue:1.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Fade color to Red
    [macro addCommand:[RKMCSlew commandWithRed:1.0 green:0.0 blue:0.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Fade color to Green
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:1.0 blue:0.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Loop End
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];
}

//Macro Shape
//Changes the Shape depending on the number of loops you include
//Example: 4 loops makes a square
//360 degrees / (4)= 90 degree turns
-(IBAction)MacroShape:(id)sender{
    
    
    
    //Create a new macro object to send to Sphero
     RKMacroObject *macro = [RKMacroObject new];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    //Change color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:1000]];
    
    // Adding sequence of macro commands to make a full shape with
    // number of sides equal to robotLoop
    for(int i = 0; i < robotLoop; i++) {
        //Come to Stop
        [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:100]];

        [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:i*(360/robotLoop) delay:robotDelay]];
    }
    
//    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];

}

//Figure 8 repeat
//RotateOverTime is a parallel command
//When a rotation action is performed, either have it run parallel to a color command or a delay.
//If the user was to include a drive command it would then end the rotation abrumtly.
-(IBAction)MacroFigureEight:(id)sender{
    //Start with verb!!
    //Give Loop
    
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Tell Robot to look forward and to start driving
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:0 delay:2000]];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    ///Tell Robot to perform 1st turn in the postive direction.
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:360 delay:robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Rotate to pertform the 2nd turn in the negitive direction
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:-360 delay:robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Come to stop
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:1000]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];

}


@end
