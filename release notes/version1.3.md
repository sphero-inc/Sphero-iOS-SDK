
## New in this version:

#### New API additions.
* **orbBasic** - Adds API support for loading, executing, aborting and erasing orbBasic programs onto Sphero. Sphero has a built in BASIC interperter, and this API provides the framework support. The class additions are:
	* **RKOrbBasicProgram** - A class to encapsulate an orbBasic program.
	* **RKOrbBasicAppendFragmentCommand** - Class for sending code fragments to append to the program storage area on Sphero. 
	* **RKOrbBasicAppendFragmentResponse** - Class for the response from a RKOrbBasicAppendFragmentCommand.
	* **RKOrbBasicExecuteCommand** - Class for sending an execute command to Sphero.
	* **RKOrbBasicExecuteResponse** - Class for the response from a RKOrbBasicExecuteCommand.
	* **RKOrbBasicAbortCommand** - Class to send an abort execution command to Sphero.
	* **RKOrbBasicAbortResponse** - Class for the response from a RKOrbBasicAbortCommand.
	* **RKOrbBasicEraseStorageCommand** - Class for sending a command to erase the program storage area.
	* **RKOrbBasicEraseStorageResponse** - Class for the response from a RKOrbBasicEraseStorageCommand.
	* **RKOrbBasicPrintMessage** - Class that will contain print message generated while a program is running.
	* **RKOrbBasicErrorASCII** - Class that contains a execution error message while running a program.
	* **RKOrbBasicErrorBinary** - Class that contains a binary error 
* Added support for turning on power state notifications in the orbotix.robot.base package. Added the classes:
	* **RKSetPowerNotificaitonCommand** - Class used to send a command to set the power state notifications on. The library will turn this off when the connection is closed.
	* **RKSetPowerNotificationResponse** - Class to encapsulate the response return from a SetPowerNotificationCommand.
	* **RKPowerNotificationAsyncData** - Class that encapsulate the power state notifications sent from Sphero.
* Added RK[Get|Set]AutoReconnectCommand and RK[Get|Set]AutoReconnectResponse to handle turning on and off the auto reconnect feature of the firmware.
* Added RKSetInactivityTimeoutCommand to set the time out Sphero uses before going to sleep.

 

#### New sample code
**OrbBasicLoader** - Sample code that demonstrates the use OrbBasicProgram to load, execute, abort, and erase orbBasic programs.

## Fixes and such:

#### In the API
- Fixed potential deadlock condition that could happen in closing down communication threads.
- Update the current heading in RKRollCommand after a RKCalibateCommand to reset the heading to the newly calibrated heading.






