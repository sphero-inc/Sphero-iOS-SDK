![logo](http://update.orbotix.com/developer/sphero-small.png)

# Sensor StreamingSphero supports asynchronous data streaming of certain control system and sensor parameters.  This is great for using Sphero as a controller, or for retrieving data about its environment.  In this document we show on Android how to setup and receive asynchronous data from Sphero.

## Available Sensor Parameters
As of Firmware 1.20, Sphero can stream the following values: 1. **Accelerometer** (X, Y, Z) 2. **GyroScope** (X, Y, Z)
 3. **IMU** (Roll, Pitch, and Yaw)
 4. **Back EMF** (Left Motor, Right Motor)
 5. **Quaternions** - *New to Firmware 1.20*
 6. **Location Data** (X, Y, Vx, Vy) - *New to Firmware 1.20*## Accelerometer

An accelerometer measures the force of gravity in 3-dimensions (x,y,z).  A few uses are for determining shake gestures and collisions. 

![android.jpg](https://github.com/orbotix/Sphero-Android-SDK/raw/master/assets/accelerometer.png)

On Sphero, you have access to the raw and filtered accelerometer data.  You should always stream the filtered data, unless you have use for the raw data.  The filtered accelerometer data is in units of g.  So, 1 G = a value of 9.81 m/s^2. 
## Gyroscope

A gyroscope is a device for measuring or maintaining orientation, based on the principles of angular momentum. It returns the rate of angular velocity.

![android.jpg](https://github.com/orbotix/Sphero-Android-SDK/raw/master/assets/gyroscope.png)## IMU
The IMU uses the accelerometer and gyroscope on Sphero to determine values for Roll, Pitch, and Yaw.  These values (in degrees) can be used to determine the orientation of Sphero.
![android.jpg](https://github.com/orbotix/Sphero-Android-SDK/raw/master/assets/IMU.png)## Back EMF

Back electromotive force (abbreviated Back EMF) is the voltage, or electromotive force, that pushes against the current which induces it.  Before we created the Locator, this could be used to determine how fast Sphero was traveling. It can still be used to determining what is going on with the motors.

## Quaternions

		Note: You need firmware 1.20 or above on Sphero, or these values will always be 0

Quaternions are a number system that extends the complex numbers.  They are used to represent orientation in 3D-space.  Typically, these are four numbers, all ranging from 0-1.  For data transmission reasons, we give you 4 numbers from 0-10000.  Hence, the units on these return numbers are (1/10000th) of a Q.  

## Locator Data

		Note: You need firmware 1.20 or above on Sphero, or these values will always be 0
		
The locator returns values for the x,y position of Sphero on the floor, and the current velocity vector of Sphero.  Please see the locator sample documentation for more information.## Requesting Data Streaming
In the Set Data Streaming command, we recommend a value of 20 <= divisor <= 50 and packetFrames=1 for most purposes.  Since the maximum sensor sampling rate is ~420 Hz, if we take divisor=20 and packetFrames=1 we get approx. 420/20 = ~21 packets/second each containing one set of requested data values.  For iOS devices divisor=20 works well.  For many Android devices divisor = 10 or less is possible (42+ samples/second).
	-(void)sendSetDataStreamingCommand {
    
    	// Requesting the Accelerometer X, Y, and Z filtered (in Gs)
    	//            the IMU Angles roll, pitch, and yaw (in degrees)
    	//            the Quaternion data q0, q1, q2, and q3 (in 1/10000) of a Q
    	RKDataStreamingMask mask =  RKDataStreamingMaskAccelerometerFilteredAll |
                                RKDataStreamingMaskIMUAnglesFilteredAll   |
                                RKDataStreamingMaskQuaternionAll;
    
    	// Note: If your ball has Firmware < 1.20 then these Quaternions
    	//       will simply show up as zeros.
    
    	// Sphero samples this data at 400 Hz.  The divisor sets the sample
    	// rate you want it to store frames of data.  In this case 400Hz/40 = 10Hz
    	uint16_t divisor = 40;
    
    	// Packet frames is the number of frames Sphero will store before it sends
    	// an async data packet to the iOS device
    	uint16_t packetFrames = 1;
    
    	// Count is the number of async data packets Sphero will send you before
    	// it stops.  You want to register for a finite count and then send the command
    	// again once you approach the limit.  Otherwise data streaming may be left
    	// on when your app crashes, putting Sphero in a bad state.
    	uint8_t count = TOTAL_PACKET_COUNT;
    
    	// Reset finite packet counter
    	packetCounter = 0;
    
    	// Send command to Sphero
    	[RKSetDataStreamingCommand sendCommandWithSampleRateDivisor:divisor
                                                   packetFrames:packetFrames
                                                     sensorMask:mask
                                                    packetCount:count];

	}
    For real time applications setting packetFrames > 1 is usually pointless since you are only interested in the most recent data.  However it is possible to obtain all the samples by setting, for instance, divisor=1 and packetFrames=21 (~20 packets/second each containing 21 sets of data.It is important to note that we are only requesting 200 sets of data from this Set Data Streaming Command.  Therefore, you will have to request after you get close to 200.  This is done to solve the problem of requesting infinite data putting the Sphero robot in a bad state if your app crashes and did not disconnect properly.   
## Receiving Async Data Packets

You will receive an `onDataReceived` callback at the frequency in which you requested data streaming.  The callback will contain `DeviceAsyncData` with a certain number of frames (also determined when requesting data).  The data will contain all the variables you requested as well.

In this example, you have access to the Attitude (IMU) data and the filtered accelerometer data. 
 
	- (void)handleAsyncData:(RKDeviceAsyncData *)asyncData
	{
    	// Need to check which type of async data is received as this method will be called for
    	// data streaming packets and sleep notification packets. We are going to ignore the sleep
    	// notifications.
    	if ([asyncData isKindOfClass:[RKDeviceSensorsAsyncData class]]) {
        
        	// If we are getting close to packet limit, request more
        	packetCounter++;
        	if( packetCounter > (TOTAL_PACKET_COUNT-PACKET_COUNT_THRESHOLD)) {
            	[self sendSetDataStreamingCommand];
        	}
        
        	// Received sensor data, so display it to the user.
        	RKDeviceSensorsAsyncData *sensorsAsyncData = (RKDeviceSensorsAsyncData *)asyncData;
        	RKDeviceSensorsData *sensorsData = [sensorsAsyncData.dataFrames lastObject];
        	RKAccelerometerData *accelerometerData = sensorsData.accelerometerData;
        	RKAttitudeData *attitudeData = sensorsData.attitudeData;
        	RKQuaternionData *quaternionData = sensorsData.quaternionData;
        
        	// Print data to the text fields
        	self.xValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.x];
        	self.yValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.y];
        	self.zValueLabel.text = [NSString stringWithFormat:@"%.6f", accelerometerData.acceleration.z];
        	self.pitchValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.pitch];
        	self.rollValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.roll];
        	self.yawValueLabel.text = [NSString stringWithFormat:@"%.0f", attitudeData.yaw];
        	self.q0ValueLabel.text = [NSString stringWithFormat:@"%d", quaternionData.quaternions.q0];
        	self.q1ValueLabel.text = [NSString stringWithFormat:@"%d", quaternionData.quaternions.q1];
        	self.q2ValueLabel.text = [NSString stringWithFormat:@"%d", quaternionData.quaternions.q2];
        	self.q3ValueLabel.text = [NSString stringWithFormat:@"%d", quaternionData.quaternions.q3];
    	}
	}## Questions

For questions, please visit our developer's forum at [http://forum.gosphero.com/](http://forum.gosphero.com/)

	  