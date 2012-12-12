
## New in this version (1.4):

#### New API additions in RobotKit.
* Deprecated **CalibrateCommand**. Now use **SetHeadingCommand** which is the same code, different name.

#### New API additions in RobotUIKit and Bundle.
* Added **RUINoSpheroConnectedViewController** with customizable URL for Sphero purchase referrals
* Added Sphero Controller Tutorial Image
* Added customizable calibration button widget called **RUICalibrateButtonGestureHandler**
	* Now with color options
	* Now with orientation to make widget pop in any direction 

#### New sample code
* **StreamingAnimation** - Demonstrates how to use Sphero as a controller to move and rotate an image on screen.
* UISample
	* Added customizable calibration button widget
	* Added better support for portrait and landscape
* HelloWorld
	* Added **NoSpheroConnectView** with customizable URL for Sphero purchase referrals

## Fixes and such:

#### In the API
* Streaming **Quaternions** now return in values of -1.0 to 1.0 instead of -10,000 to 10,0000

#### In the samples
	
 	



