//
//  ViewController.m
//  RobotUISample
//
//  Created by Jon Carroll on 12/9/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//

#import "ViewController.h"

#import "RobotKit/RobotKit.h"

#import "RobotUIKit/RobotUIKit.h"

@implementation ViewController

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
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

    /*Only start the blinking loop when the view loads*/
    robotOnline = NO;

    // Setup a calibration gesture handler on our view to handle button
    // gestures and give visual feeback to the user.  Defaults to above
    calibrateAboveHandler = [[RUICalibrateButtonGestureHandler alloc]
                        initWithView:self.view
                        button:calibrateAboveButton];
    
    // Make the size of the calibration widget smaller for phones
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        calibrateAboveHandler.calibrationRadius = 200;
    }
    // Larger for iPads
    else {
        calibrateAboveHandler.calibrationRadius = 500;
    }
    // Open the circle widget above the button, can switch to pop out and cardinal direction
    calibrateAboveHandler.calibrationCircleLocation = RUICalibrationCircleLocationAbove;
    // Change color of the button
    [calibrateAboveHandler setBackgroundWithColor:[UIColor colorWithRed:0.1 green:0.5 blue:1 alpha:1]];
    [calibrateAboveHandler setForegroundWithColor:[UIColor colorWithRed:1 green:1 blue:1 alpha:1]];
    
    // Setup two finger two calibration method
    calibrateTwoFingerHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return UIInterfaceOrientationIsPortrait(interfaceOrientation);
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
    robotOnline = YES;
    
    //Setup joystick driving
    [RKDriveControl sharedDriveControl].joyStickSize = circularView.bounds.size;
    [RKDriveControl sharedDriveControl].driveTarget = self;
    [RKDriveControl sharedDriveControl].driveConversionAction = @selector(updateMotionIndicator:);
    [[RKDriveControl sharedDriveControl] startDriving:RKDriveControlJoyStick];
    //Set max speed
    [RKDriveControl sharedDriveControl].velocityScale = 0.6;
    
    [[RKDriveControl sharedDriveControl] startDriving:RKDriveControlJoyStick];
    
    // start processing the puck's movements
    UIPanGestureRecognizer* panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handleJoystickMotion:)];
    [drivePuck addGestureRecognizer:panGesture];
    [panGesture release];
}

-(void)setupRobotConnection {
    /*Try to connect to the robot*/
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline) name:RKDeviceConnectionOnlineNotification object:nil];

    [[RKRobotProvider sharedRobotProvider] openRobotConnection];

}

#pragma mark -
#pragma mark Joystick related methods

- (void)handleJoystickMotion:(id)sender
{
    //Don't handle the gesture if we aren't connected to and driving a robot
    //if (![RKDriveControl sharedDriveControl].driving) return;
    
    //Handle the pan gesture and pass the results into the drive control
    UIPanGestureRecognizer *pan_recognizer = (UIPanGestureRecognizer *)sender;
    CGRect parent_bounds = circularView.bounds;
    CGPoint parent_center = [circularView convertPoint:circularView.center fromView:circularView.superview] ;
    
    if (pan_recognizer.state == UIGestureRecognizerStateEnded || pan_recognizer.state == UIGestureRecognizerStateCancelled || pan_recognizer.state == UIGestureRecognizerStateFailed ) {
        ballMoving = NO;
        [RKRollCommand sendStop];
        drivePuck.center = parent_center;
    } else if (pan_recognizer.state == UIGestureRecognizerStateChanged || pan_recognizer.state == UIGestureRecognizerStateBegan) {
        ballMoving = YES;
        CGPoint translate = [pan_recognizer translationInView:circularView];
        CGPoint drag_point = parent_center;
        drag_point.x += translate.x;
        drag_point.y += translate.y;
        drag_point.x = [self clampWithValue:drag_point.x min:CGRectGetMinX(parent_bounds) max:CGRectGetMaxX(parent_bounds)];
        drag_point.y = [self clampWithValue:drag_point.y min:CGRectGetMinY(parent_bounds) max:CGRectGetMaxY(parent_bounds)];
        [[RKDriveControl sharedDriveControl] driveWithJoyStickPosition:drag_point];
        [self convertWithCoord1:drag_point.x coord2:drag_point.y coord3:0.0];
    }
}

- (void) convertWithCoord1:(double)x coord2:(double)y coord3:(double)unused
{
    double angle, velocity;
    CGRect parent_bounds = circularView.bounds;
    CGPoint center = CGPointMake(CGRectGetMidX(parent_bounds), CGRectGetMidY(parent_bounds));
    double x_length = x - CGRectGetMidX(parent_bounds);
    double y_length = CGRectGetMidY(parent_bounds) - y;
    
    // Need to scale x_length and y_length to make sure the coordinates are polar
    // instead of eliptical
    if (center.x > center.y) {
        x_length *= center.y/center.x;
    } else if (center.x < center.y) {
        y_length *= center.x/center.y;
    }
    
    if (center.x > 0.0 && center.y > 0.0) {
        velocity = (sqrt(x_length * x_length + y_length * y_length) /
                    fmin(center.x, center.y));
        velocity = Clamp(velocity, 0.0, 1.0) * 0.6;
    } else {
        velocity = 0.0;
    }
    
    // calculate the angle
    angle = atan2(x_length, y_length);
    if (angle < 0.0) { // adjust for range between 0 and 2π
        angle += 2.0 * M_PI;
    }
    // correct angle
    //self.angle -= correctionAngle;
    if (angle < 0.0) {
        angle += 2.0 * M_PI;
    }
    
    angle *= 180.0/M_PI; // convert to degrees
    
    [RKRollCommand sendCommandWithHeading:angle velocity:velocity];
    RKDriveAlgorithm *drive = [[RKDriveAlgorithm alloc] init];
    drive.velocity = velocity;
    drive.angle = angle;
    drive.velocityScale = 0.6;
    drive.correctionAngle = 0.0f;
    [self updateMotionIndicator:drive];
    [drive release];
    
}

- (void)updateMotionIndicator:(RKDriveAlgorithm*)driveAlgorithm {
    //Don't update the puck position if we aren't driving
    if ( ![RKDriveControl sharedDriveControl].driving || !ballMoving) return;
    
    //Update the joystick puck position based on the data from the drive algorithm
    CGRect bounds = circularView.bounds;
    
    double velocity = driveAlgorithm.velocity/driveAlgorithm.velocityScale;
	double angle = driveAlgorithm.angle + (driveAlgorithm.correctionAngle * 180.0/M_PI);
	if (angle > 360.0) {
		angle -= 360.0;
	}
    double x = ((CGRectGetMaxX(bounds) - CGRectGetMinX(bounds))/2.0) *
    (1.0 + velocity * sin(angle * M_PI/180.0));
    double y = ((CGRectGetMaxY(bounds) - CGRectGetMinY(bounds))/2.0) *
    (1.0 - velocity * cos(angle * M_PI/180.0));
	
    CGPoint center = CGPointMake(floor(x), floor(y));
    
    [UIView setAnimationsEnabled:NO];
    drivePuck.center = center;   
    [UIView setAnimationsEnabled:YES];
}

- (float)clampWithValue:(float)value min:(float)min max:(float)max {
    //A standard clamp function
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

#pragma mark -
#pragma mark UI Interaction

-(IBAction)colorPressed:(id)sender {
    //RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
    NSString* rootpath = [[NSBundle mainBundle] bundlePath];
    NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
    NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
    
    //Present the color picker and set the starting color to white
    RUIColorPickerViewController *colorPicker = [[RUIColorPickerViewController alloc] initWithNibName:@"RUIColorPickerViewController" bundle:ruiBundle];
    [colorPicker setCurrentRed:1.0 green:1.0 blue:1.0];
    colorPicker.delegate = self;
    [self presentModalLayerViewController:colorPicker animated:YES];
    [colorPicker release];
}

//Color picker delegate callbacks
-(void) colorPickerDidChange:(UIViewController*)controller withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b {
    //Send the color to Sphero when the user picks a new color in the picker
    [RKRGBLEDOutputCommand sendCommandWithRed:r green:g blue:b];
}


-(void) colorPickerDidFinish:(UIViewController*)controller withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b {
    //Use this callback to dismiss the color picker, since we are presenting it as a modalLayerViewController it will dismiss itself
}

-(IBAction)sleepPressed:(id)sender {
    //RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
    NSString* rootpath = [[NSBundle mainBundle] bundlePath];
    NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
    NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
    
    //Present the slide to sleep view controller
    RUISlideToSleepViewController *sleep = [[RUISlideToSleepViewController alloc] initWithNibName:@"RUISlideToSleepViewController" bundle:ruiBundle];
    sleep.view.frame = self.view.bounds;
    [self presentModalLayerViewController:sleep animated:YES];
    [sleep release];
}

-(BOOL)calibrateGestureHandlerShouldAllowCalibration:(RUICalibrateButtonGestureHandler*)sender {
    return YES;
}

- (void)dealloc {
    [calibrateTwoFingerHandler release];
    [calibrateAboveHandler release];
    [calibrateAboveButton release];
    [super dealloc];
}

@end
