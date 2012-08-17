![logo](http://update.orbotix.com/developer/sphero-small.png)

# Collision DetectionSphero collision detection is a firmware feature that generates a collision async message when an impact is detected. The detection criteria is based on threshold parameters set via the phone.
## Detection FeaturesThe collision detection feature detects impacts on the X and Y axis of Sphero.The Y axis runs through the forward/backward line of Sphero. The X axis runs from side to side. The Z axis run up and down, but is not a factor in the current implementation.
It detects collisions by measuring the accelerometer values and calculating the power (energy) of the signal in real time. When the power exceeds a threshold value, a collision is reported.
## Detection ThresholdsThe X and Y axis impact thresholds are controlled independently. Each axis has two threshold values, the power of an impact, and a bias based on the speed of the ball. Xt is the threshold for the X axis at a speed of zero. The Xspd bias is added to Xt and becomes the threshold at the maximum speed.
Typical values are in the 40-100 range for Xt and Yt.  Typical values for the speed thresholds Xspd and Yspd are 50-100.  

These values are dependent on the types of collisions you want to detect.  For example, if you only want to detect serious impacts when the ball hits a wall you should set these paramers:

	Wall Hits: Xt=200, Xsp=0, Yt=125, Ysp=0, deadTime=100 (1 second)
	
These values suggest only pay attention to a power threshold over 125 in the y-direction. And a x threshold over 200 is too high to occur while driving.  The deadTime means that after the ball detects a collision, it will delay any more collisions for 1 second after.  This is to avoid multiple collision async packets from one collision.

Ball to ball collisions is a little bit tougher to determine, since Sphero may trigger collisions just driving aorund. However, these parameters will get you fairly accurate collisions at any point on the ball.

	Ball to Ball Hits: Xt=40, Xsp=60, Yt=40, Ysp=60, deadTime=40 (400 ms)
	
These values suggest a low collision threshold when you are not moving, and a higher one when Sphero is driving at full power. That way, we will minimize the false collisions when just driving around.  This also will trigger collisions on both axis.  We don't want the deadTime to be as high here, because if we get a false collision before an actual collision, we don't want to ignore the real one.
## Enabling Collision Detection
Collision Detection is enabled via the Configure Collision Detection command.  The Method field should be set to RKCollisionDetectionMethod1, and the X and Y axis impact thresholds should be set, along with the deadTime. The code to configure collision detection is:

    [RKConfigureCollisionDetectionCommand sendCommandForMethod:RKCollisionDetectionMethod1
                                                    xThreshold:xThreshold
                                               xSpeedThreshold:xSpeedThreshold
                                                    yThreshold:yThreshold
                                               ySpeedThreshold:ySpeedThreshold
                                              postTimeDeadZone:deadTime];    
                                              
## Registering for Collision Async Data

As with data streaming, you have to register for async data notifications with this line of code after you configure the collision detection:

	[[RKDeviceMessenger sharedMessenger] addDataStreamingObserver:self
                                                         selector:@selector(handleAsyncData:)];                                        After this, you must add a method called handleAsyncData that will check for async data of type *RKCollisionDetectedAsyncData*: 	- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
	{
	    if ([asyncData isKindOfClass:[RKCollisionDetectedAsyncData class]]) {
	    
	        RKCollisionDetectedAsyncData *collisionData = (RKCollisionDetectedAsyncData *)asyncData;
	    	
	    	// Analyze the data
	    }
	}## Understanding Collision DataAn impact is reported via an asynchronous messages to the phone.  The details of the impact are reported using two different methodologies.First, the actual power impact value is given in xMagnitude and yMagnitude. These values are the power that was detected in the impact and were compared to the threshold to determine a reportable collision. The Axis field indicates which (or both) axis crossed the threshold and is being reported.  In the sample of code, these values are:

	RKCollisionDetectedAsyncData *collisionData = (RKCollisionDetectedAsyncData *)asyncData;
	        
	collisionData.impactAxis.x;
	collisionData.impactAxis.y;
		
	collisionData.impactPower.x;
	collisionData.impactPower.y;
The second methodology is the impact values read from the accelerometer at the highest peak of impact. X and Y are the "flattened" values given by the accelerometer, and are calculated by removing the Z axis influence. In other words, they represent impact values only on the plane of the surface that Sphero is running on. X and Y have both positive and negative values. Positive values are based on the front (Y) and right (X) side of the ball. The Z reported value is always zero.  Also, the speed of the ball at the time of the reported impact is given by the Speed output. The values can be received in code by:
	collisionData.impactAcceleration.x;      
	collisionData.impactAcceleration.y;           
	collisionData.impactSpeed;The timestamp can be used to synchronize collisions in a multi-ball scenario.	collisionData.impactTimeStamp;## Questions

For questions, please visit our developer's forum at [http://forum.gosphero.com/](http://forum.gosphero.com/)