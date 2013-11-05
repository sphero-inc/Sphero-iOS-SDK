![iosdeveloperheader.jpg](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/assets/image00.jpg)

# iOS Developer Quick Start Guide

## Resources

### Class Documentation

---

 The class documentation is located in api/ as DocSets for use with Xcode. It can be installed by following the Sphero SDK installation steps below. If that does not work or you would like to install the DocSets manually you can simply copy them into the DocSets directory used by Xcode. It is located at
 
        ~/Library/Developer/Shared/Documentation/DocSets/
 
Once the DocSets have been copied, restart Xcode and they will then appear in the Documentation section of the Organizer.

---

### Community and Help

**Keep up to date by watching our [Sphero iOS GitHub Repository](https://github.com/orbotix/Sphero-iOS-SDK) **
  
**Share your project, get help, and chat with Sphero developers at [Sphero Developer Forum](http://forum.gosphero.com/) **



## Overview

 
This Guide walks you through the basics of creating mobile apps for iOS that leverage the Orbotix Sphero SDK. The examples in this guide were built using Objective-C and have been tested with the current released OS and current version of Xcode. The goal of this developer guide along with sample code is to give the developer a taste of the wide variety of things Sphero can do, respond to, and keep track of.

*In general this guide will walk you through:*

 - Installing the SDK
 - Changing Sphero's Color
 - Using the Roll Command to move Sphero 

### Before we begin - Installing Xcode

    Notice: The Sphero iOS SDK works with iOS 5.0+

Before you begin to develop applications that interface with Sphero on iOS, you will need to install the iOS developer tools. There is a general assumption that you are using the latest version of Mac OSX, our software is designed to take advantage of all the most current technologies that are offered but it is possible that it will work on older frameworks and technologies.

 - Download and Install the current version of [Xcode](http://developer.apple.com/technologies/xcode.html) 

## Installing the Sphero iOS SDK

There are two ways to integrate the Sphero SDK into your project. You can start a new project that is preconfigured to communicate with Sphero or you can add the RobotKit and RobotUIKit to an existing project. Starting a new project is the fastest way to begin developing applications that utilize and control Sphero.

&nbsp;
### Starting a new Project

  Please see the [1.6 release notes](https://github.com/orbotix/Sphero-iOS-SDK/release%20notes/version1.6.md) for setting up a new project or follow the following Integrating with existing project section)

&nbsp;
### Integrating into an existing project

There are always those cases where you already developed an awesome game or app and want to integrate Sphero functionality or controllability into the project. For those cases we have made it possible to integrate our libraries into your existing project, including some nifty pre-built user interface tools.

 - Download the current [Sphero iOS SDK](https://github.com/orbotix/Sphero-iOS-SDK/zipball/master).

 - Simply Drag `RobotKit.framework`, `RobotUIKit.framework` and `RobotUIKit.Bundle` into your project's framework folder.

![sendingIn.png](https://github.com/orbotix/Sphero-iOS-SDK/raw/master/assets/image03.png)

**!NOTICE: It is important to note that you must also include:** `ExternalAccessory.framework`, `CoreMotion.framework`

**!NOTICE: There are some linker changes that also must be made:** 
Change Build Settings -> Linking -> Other Linker Flags

		-lstdc++
		-all_load
		-ObjC
		-lsqlite3

**!NOTICE: You need to add the external accessory protocol string to your Info.plist.:** 
Edit the Info.plist for your application target and add an entry for key "Supported external accessory protocols" which will create an array. Add "com.orbotix.robotprotocol" as a String item in the array.

 The HelloSphero example has all the necessary code needed to create and maintain a connection to Sphero, and can be used as a guide in best practices.  In general you will need to:

 - You should define two methods in your `.h`, One to Setup the connection to Sphero and one to maintain the connection.

        BOOL robotOnline;
        -(void)setupRobotConnection;
        -(void)handleRobotOnline;

 - Make sure to import RobotKit.h

        #import <RobotKit/RobotKit.h>

 - Create a method to handle setting up the Connection to Sphero

        -(void)connectToRobot 
        {	
			[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleRobotOnline:) name:RKDeviceConnectionOnlineNotification object:nil];
		if ([[RKRobotProvider sharedRobotProvider] isRobotUnderControl]) 
		{
			[[RKRobotProvider sharedRobotProvider] openRobotConnection];
		}else
		{
			[[RKRobotProvider sharedRobotProvider] controlConnectedRobot];
		}
		
- Create a method to handle maintaining the Connection to Sphero

        - (void)handleRobotOnline {
            /*The robot is now online, we can begin sending commands*/
            if(!robotOnline) {
                /* Send commands to Sphero Here: */

            }
            robotOnline = YES;
        }

 - Overload the `appDidBecomeActive:(NSNotification*)notification` method and initialize the connection to Sphero

    
        -(void)appDidBecomeActive:(NSNotification*)notification {
            /*When the application becomes active after entering the background we try to connect to the robot*/
            [self connectToRobot];
        }

 - In the `OnLoad()` method you should register for application lifecycle notifications 

        - (void)viewDidLoad
        {
            [super viewDidLoad];
	        // Do any additional setup after loading the view, typically from a nib.

            /*Register for application lifecycle notifications so we known when to connect and disconnect from the robot*/
           [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appDidBecomeActive:) name:UIApplicationDidBecomeActiveNotification object:nil];
           [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appWillResignActive:) name:UIApplicationWillResignActiveNotification object:nil];

            robotOnline = NO;
        }


 - Do not forget to Disconnect from the Robot when the app closes, otherwise next time you start a connection it will already be in use.

        -(void)appWillResignActive:(NSNotification*)notification {
            /*When the application is entering the background we need to close the connection to the robot*/
            [[NSNotificationCenter defaultCenter] removeObserver:self name:RKDeviceConnectionOnlineNotification object:nil];
            [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];
            [[RKRobotProvider sharedRobotProvider] closeRobotConnection];
            robotOnline = NO;
        }

 You are now ready to start controlling and receiving information from your Sphero, simply add the following to change the LED Color of Sphero to red:

     [RKRGBLEDOutputCommand sendCommandWithRed:1.0 green:0.0 blue:0.0];


&nbsp;
## Using the Sphero iOS SDK


If you started poking around in the template project you may have noticed that inside `ViewController.m` there are some commands to set the RGB LED on Sphero. This is best way to change Sphero’s color and give visual feedback using the ball.
This command is described in section 3 in more detail but it is a good exercise at this point to change these values and try it out, play around a little bit.

**For example**, try changing the following command in `ViewController.m` from

    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green :0.0 blue :1.0];

to

    [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green :1.0 blue :0.0];

Notice the change from green of 0.0 to a green of 1.0. Run it and you should have a Green Sphero!  

&nbsp;
### Sending Roll Commands

 - Using Roll Commands to **Move** Sphero.

 - Using Roll Commands to **Stop** Sphero.

So, you got the LED to blink… thats Awesome! But let's also take advantage of the amazing technology inside Sphero and drive the ball around a little bit. 
	
In order to move Sphero you will need to send a RollCommand. The RollCommand takes two parameters.

   1. Heading in degrees from 0° to 360° 
   2.  Speed from 0.0 to 1.0. 

For example, a heading of 90° at a speed of 0.5 will tell Sphero to turn clockwise 90° at half speed (1.0 is full speed). Once this command is issued Sphero will continue at this heading and speed until it hits something or runs out of range, so you will need to stop the ball using the RollCommand and `sendStop()`.


Now, it's time to modify the code. Let's send Sphero forward for 2 seconds. Next we will create 2 new methods, one to Move Sphero, and Delay. And another to Stop Sphero.

			- (void)stop {
		    	[RKRollCommand sendStop];
			}
			
			- (void)driveforward {
				[RKRollCommand sendCommandWithHeading:0.0 velocity:0.5];			
				[self performSelector:@selector(stop) withDelay:2.0];
			}


Next add the following code in place of the RGB command that was sent before.


		    [self driveforward];


**Run the application on an iOS Device, if all went well Sphero should have moved forward just a little.**


&nbsp;
## Where is Sphero going?

If you have successfully completed the quick start guide then Sphero should have moved after running the modified code.  What is interesting to note here is that Sphero just went in a *random* direction.  The direction was not random at all, Sphero believe it or not has a *front* and a *back*.  It is necessary for the application to determine what direction forward is for the user from the point of view of the ball.  We call this step `Calibration` and it is **required** to properly drive Sphero in a predictable direction.  To learn more about calibration and using the `BackLED` to set Sphero's orientation please check out the `UISampler` Sample project.
		    
		    
		    

&nbsp;
&nbsp;

### Samples

---

 * [HelloWorld](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/HelloWorld) - Connect to Sphero and blink the LED.  This is the most compact and easy to follow sample for dealing with Sphero.  It is also the default project for the template installer.

* [ButtonDrive](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/ButtonDrive) - Drive Sphero with simple buttons on screen, just a notch above helloworld.

* [RobotUISample](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/RobotUISample) - RobotUISample is a great place to start, it already has elements for two finger calibration, shows you how to use sleep and colorpicker and also has a drive wheel!  

* [SensorStreaming](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/SensorStreaming) - If you want to use the sensor data from Sphero, you should check this sample out.  Just simply register as an observer to the data, Pay attention to starting and stoping streaming during the application life cycle.

* [RKMultiplayer Sample](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/RKMultiplayerSample) - Check out our base sample for connecting two or more phones to a multiplayer lobby, cross platform.  This would be the place to start if you want to make party games or anything multiplayer.

* [SphereMotion Teapot](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/SphereMotionTeapot) - This is a sensor streaming application that shows you how to use 3D objects in the screen, the simple teapot, driving by Sphero's motion.

* [RKAchievement Sample](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/AchievementSample) - Sphero has a backend web service that can help you maintain Achievements and also keeps track of all the Sphero activity, engage with your users!

* [TwoPhonesOneBall](https://github.com/orbotix/Sphero-iOS-SDK/tree/master/samples/TwoPhonesOneBall) - A quick sample to show passing control between two phones to control a single Sphero.

		


		




























