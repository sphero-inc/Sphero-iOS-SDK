## New in this version (1.6 b1146):

## Hotfix 4.14.2014 - Fixes for crashing on iOS 7.1/xCode 5.1 - Updated RobotKit.framework and placed in all sample code

## Fixes:

#### Support for XCode 5 & iOS7

SDK is compatible with Xcode5 and iOS versions 5 through 7 with native support for armv7 and armv7s.  The QuickStart App template has been removed from this release since XCode 5 is not compatible.  Please use the following information to manually setup your project.  

##### Projects using this SDK MUST:
 * In Project Info
    * Target **iOS6**
 * In Build Settings
 	* Architecures - **Standard Architectures (armv7, armv7s)**
 	* Valid Architectures - **armv7 armv7s** (remove arm64)
 		* arm64 cannot be supported with iOS5 support - removal of iOS5 support and support for arm64 will be delivered as another download.
 	* Other Linker Flags - add **-lstdc++**
 * Add required Frameworks
 	* **RobotKit.framework**
 	* CoreMotion.framework
 	* libsqlite3.0.dylib
 	* ExternalAccessory.framework
 * In yourAppName-Info.plist
 	* Add "Supported External Accessories Protocol"
 		* Value = **com.orbotix.robotprotocol**
 	 

#### SDK Connection Usage

	In the App Delegate - call 'connectToRobot'

	#import <RobotKit/RobotKit.h>
	
	...
	
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
	}
	
	/** notification that Robot is Online and ready for use */
	-(void) handleRobotOnline:(NSNotification*) n
	{
		RKRobot *robot = [n.userInfo objectForKey:@"robot"];
		NSLog(@"Connected %@", robot);
	}

	...


 	



