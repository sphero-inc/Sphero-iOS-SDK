# Robot UI Sample
## Color Picker

The `RUIColorPickerViewController` presents a color wheel and a brightness bar along with a couple preview windows and an RGB readout. This is a very easy way for a user to change the color of their Sphero™.

![Color Picker](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/RobotUISample/iosColor.png)

The color changes initiated by the user are delivered to the RUIColorPickerViewController's delegate. 

To set up the View Controller, you must first obtain a reference to the RobotUIKit bundle that contains the necessary assets. 

```objective-c
//RobotUIKit resources like images and nib files stored in an external bundle and the path must be specified
NSString* rootpath = [[NSBundle mainBundle] bundlePath];
NSString* ruirespath = [NSBundle pathForResource:@"RobotUIKit" ofType:@"bundle" inDirectory:rootpath];
NSBundle* ruiBundle = [NSBundle bundleWithPath:ruirespath];
```

Now you can create the `RUIColorPickerViewController`.

```objective-c
RUIColorPickerViewController *colorPicker = [[RUIColorPickerViewController alloc] initWithNibName:@"RUIColorPickerViewController" bundle:ruiBundle];
```

To ensure the color picker starts on the correct color, you must set the color properties in the view controller. 

```objective-c
[colorPicker setCurrentRed:self.currentRed green:self.currentGreen blue:self.currentBlue];
```

To receive the color change callbacks, you must implement the `RUIColorPickerDelegate` protocol,

```objective-c
@interface ViewController : UIViewController <RUIColorPickerDelegate> { …
```

implement the `colorPickerDidChange: withRed: green: blue: method`,

```objective-c
-(void) colorPickerDidChange:(UIViewController*)controller withRed:(CGFloat)r green:(CGFloat)g blue:(CGFloat)b {
    //Send the color to Sphero when the user picks a new color in the picker
    [RKRGBLEDOutputCommand sendCommandWithRed:r green:g blue:b];
}
```

and you must set the color picker's delegate.

```objective-c
colorPicker.delegate = self;
```

Once everything is set up, you can present the view controller.

```objective-c
[self presentModalLayerViewController:colorPicker animated:YES];
[colorPicker release];
```

If you need to do anything when the color picker is finished you can also implement the `colorPickerDidFinish: withRed: green: blue:` method.

## Calibration View

The calibration view can be used to give the user some visual feedback while "aiming" their Sphero. It is meant to be an "all in one" widget combining the rotation gesture detection with the visual representation of calibration while sending the commands to Sphero to actually rotate and calibrate when finished.

![Calibration View](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/RobotUISample/iosCalibration.png)

To set up the `RUICalibrateGestureHandler`, simply create one with your View Controller's view.

```objective-c
//set up a calibration gesture handler on our view to handle rotation gestures and give visual feeback to the user.
calibrateHandler = [[RUICalibrateGestureHandler alloc] initWithView:self.view];
```

Then, when a rotation gesture is recognized, the `RUICalibrateGestureHandler` automatically displays the calibration rings on the screen and sends the rotation and calibration commands to the connected Sphero. 

## Joystick View

The joystick view is just one of the ways a user can control Sphero. One of the benefits of a joystick over a two lever RC style control is ability to give direction to Sphero relative to the user's orientation. So, if the user remains stationary and facing the same direction, pushing the joystick puck away always makes Sphero travel in the same direction.

![Joystick View](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/RobotUISample/joystick.jpg)

Driving Sphero with a joystick view can be broken down into three parts.

1. **The touch interaction**  
When a user moves the joystick puck with their finger, they are touching a point inside the circle. To get that point, you can use a `UIPanGestureRecognizer` and calculate the point in the circle relative to the center point.

2. **The conversion into a roll**  
`RKDriveControl` was made exactly for this purpose. After finding the point inside the joystick circle, you can feed that point directly into the Drive Control. The Drive Control will then interpret that point as a vector from the center of the wheel and send Sphero rolling in that direction and velocity.

3. **The updating of the joystick UI**  
After `RKDriveControl` converts the point into an angle and velocity, it delivers those values back to its conversion target. This is a perfect time to update the puck's position by converting those values back into a position on the wheel. This is especially useful when using this same concept with a tilt control where accelerometer values are converted into an angle and velocity and displayed to the user with no touch interaction at all.

To achieve this flow you must first set up the Drive Control by giving it the size of your joystick wheel, setting the conversion action, and starting the joystick driving (don't forget to set the max speed for Sphero).

```objective-c
[RKDriveControl sharedDriveControl].joyStickSize = circularView.bounds.size;
[RKDriveControl sharedDriveControl].driveTarget = self;
[RKDriveControl sharedDriveControl].driveConversionAction = @selector(updateMotionIndicator:);
[[RKDriveControl sharedDriveControl] startDriving:RKDriveControlJoyStick];
//Set max speed
[RKDriveControl sharedDriveControl].velocityScale = 0.6;
```
Your conversion action method should update the position of the joystick puck based on the values of the drive angle and velocity contained in the `DriveAlgorithm` passed in. Something like the following.

```objective-c
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
```

Now, you can set up the `UIPanGestureRecognizer` to interpret the user touches.

```objective-c
UIPanGestureRecognizer* panGesture = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handleJoystickMotion:)];
[drivePuck addGestureRecognizer:panGesture];
[panGesture release];
```

And setup the action method to convert the touch into a point on the joystick circle.

```objective-c
- (void)handleJoystickMotion:(id)sender
{
    //Don't handle the gesture if we aren't connected to and driving a robot
    if (![RKDriveControl sharedDriveControl].driving) return;
    
	UIPanGestureRecognizer *pan_recognizer = (UIPanGestureRecognizer *)sender;
	CGRect parent_bounds = circularView.bounds;
	CGPoint parent_center = [circularView convertPoint:circularView.center fromView:circularView.superview] ;
    
	if (pan_recognizer.state == UIGestureRecognizerStateEnded || pan_recognizer.state == UIGestureRecognizerStateCancelled || pan_recognizer.state == UIGestureRecognizerStateFailed || pan_recognizer.state == UIGestureRecognizerStateBegan) {
    	ballMoving = NO;
	    [[RKDriveControl sharedDriveControl].robotControl stopMoving];
	    drivePuck.center = parent_center;
	} else if (pan_recognizer.state == UIGestureRecognizerStateChanged) {
	    ballMoving = YES;
	    CGPoint translate = [pan_recognizer translationInView:circularView];
	    CGPoint drag_point = parent_center;
	    drag_point.x += translate.x;
	    drag_point.y += translate.y;
	    drag_point.x = [self clampWithValue:drag_point.x min:CGRectGetMinX(parent_bounds) max:CGRectGetMaxX(parent_bounds)];
	    drag_point.y = [self clampWithValue:drag_point.y min:CGRectGetMinY(parent_bounds) max:CGRectGetMaxY(parent_bounds)];
	    [[RKDriveControl sharedDriveControl] driveWithJoyStickPosition:drag_point];        
	}
}
```