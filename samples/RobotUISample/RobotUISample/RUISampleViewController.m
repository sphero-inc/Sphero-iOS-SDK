//
//  Copyright (c) 2011-2015 Orbotix, Inc. All rights reserved.
//

#import "RUISampleViewController.h"
#import <RobotUIKit/RobotUIKit.h>

@interface RUISampleViewController () <RKUIJoystickViewControllerDelegate>

@property (strong, nonatomic) RKConvenienceRobot* robot;
@property (strong, nonatomic) RKJoyStickDriveAlgorithm *driveAlgorithm;

//Views that make up the drive joystick
@property (strong, nonatomic) RKUIJoystickViewController *joystickViewController;

// Buttons from NIB that link to a calibration gesture handler
@property (strong, nonatomic) IBOutlet UIButton *calibrateAboveButton;

// Controls calibration gestures
@property (strong, nonatomic) RUICalibrateButtonGestureHandler *calibrateAboveHandler;

// Controls two finger calibration gestures
@property (strong, nonatomic) RUICalibrateGestureHandler *calibrateTwoFingerHandler;

// Robot state variables
@property (nonatomic) BOOL allowCalibrating;

@end

@implementation RUISampleViewController

- (void)viewDidLoad {
	[super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
	
	/*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(appDidBecomeActive:)
												 name:UIApplicationDidBecomeActiveNotification
											   object:nil];
	
	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(appWillResignActive:)
												 name:UIApplicationWillResignActiveNotification
											   object:nil];
	
	// Setup a calibration gesture handler on our view to handle button
	// gestures and give visual feeback to the user.  Defaults to above
	self.calibrateAboveHandler = [[RUICalibrateButtonGestureHandler alloc] initWithView:self.view button:_calibrateAboveButton];
	
	// Make the size of the calibration widget smaller for phones
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
		_calibrateAboveHandler.calibrationRadius = 200;
	}
	// Larger for iPads
	else {
		_calibrateAboveHandler.calibrationRadius = 500;
	}
	// Open the circle widget above the button, can switch to pop out and cardinal direction
	_calibrateAboveHandler.calibrationCircleLocation = RUICalibrationCircleLocationAbove;
	// Change color of the button
	[_calibrateAboveHandler setBackgroundWithColor:[UIColor colorWithRed:0.1 green:0.5 blue:1 alpha:1]];
	[_calibrateAboveHandler setForegroundWithColor:[UIColor colorWithRed:1 green:1 blue:1 alpha:1]];
	
	// Setup two finger two calibration method
	self.calibrateTwoFingerHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
    
	// listen for robots
	[[RKRobotDiscoveryAgent sharedAgent] addNotificationObserver:self selector:@selector(handleRobotStateChangeNotification:)];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	return UIInterfaceOrientationIsPortrait(interfaceOrientation);
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    [self setJoystickViewController:segue.destinationViewController];
    [_joystickViewController setJoystickDelegate:self];
}

- (void)appWillResignActive:(NSNotification*)notification {
	/*When the application is entering the background we need to close the connection to the robot*/
	[_robot setLEDWithRed:0 green:0 blue:0];
    [RKRobotDiscoveryAgent disconnectAll];
}

- (void)appDidBecomeActive:(NSNotification*)notification {
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
            [self dismissViewControllerAnimated:YES completion:nil];
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
    [_calibrateAboveHandler setRobot:_robot.robot];
    
    // start processing the puck's movements
    [_joystickViewController enableJoystick];
}

- (void)handleDisconnected {
    [_calibrateAboveHandler setRobot:nil];
    [_joystickViewController disableJoystick];
}

- (IBAction)colorPressed:(id)sender {
 	//Present the color picker and set the starting color to white
	RUIColorPickerViewController *colorPicker = [[RUIColorPickerViewController alloc] init];
	[colorPicker setCurrentRed:1.0 green:1.0 blue:1.0];
	colorPicker.delegate = self;
    [self presentViewController:colorPicker animated:YES completion:nil];
}

//Send the color to Sphero when the user picks a new color in the picker
- (void)colorPickerDidChange:(UIViewController*)controller withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b {
	[_robot setLEDWithRed:r green:g blue:b];
}

- (void)colorPickerDidFinish:(UIViewController*)controller withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b {
	//Use this callback to dismiss the color picker, since we are presenting it as a modalLayerViewController it will dismiss itself
}

- (IBAction)sleepPressed:(id)sender {
	//Present the slide to sleep view controller
	RUISlideToSleepViewController *sleep = [[RUISlideToSleepViewController alloc] init];
	sleep.view.frame = self.view.bounds;
	[sleep setDelegate:self];
    [self presentViewController:sleep animated:YES completion:nil];
}

- (void)slideToSleepConfirmed:(id)sleepView {
	[_robot sleep];
}

- (BOOL)calibrateGestureHandlerShouldAllowCalibration:(RUICalibrateButtonGestureHandler*)sender {
	return YES;
}

#pragma mark Joystick

- (void)joystickDidMoveWithHeading:(float)heading andVelocity:(float)velocity {
    [_robot driveWithHeading:heading andVelocity:velocity];
}

- (void)joystickDidStop {
    [_robot stop];
}

@end