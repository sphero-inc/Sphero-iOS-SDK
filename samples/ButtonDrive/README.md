![logo](http://update.orbotix.com/developer/sphero-small.png)

# ButtonDrive
This sample code demonstrates sending Sphero roll commands.  4 buttons on the UI will allow you to
send Sphero roll commands at 0, 90, 180 and 270 degrees.  The stop button in the middle will stop
Sphero.

![Screen Shot](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/samples/ButtonDrive/assets/image01.png)

The roll command 
takes a heading from 0° to 360°, and a relative speed from 0.0 to 1.0. So, to command the ball to go 90° at half speed would be:
     [RKRollCommand sendCommandWithHeading:90.0 velocity:0.5];
The ball is stopped with `[RKRollCommand sendStop]`.

Also, demonstrated in the code is the use of RUICalibrateGestureHandler which is attached to a view in it's initWithView: method. Calibration is used by the user to aim Sphero in a direction that they consider forward and sets the 0° heading in that direction. This gesture uses two fingers to rotate the ball similar to using two using the two finger rotation gesture used to rotate a photo.

