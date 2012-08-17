
## New in this version:

#### New API additions.
* Locator - The locator API allows you to stream position, and speed as Sphero moves. (Added in firmware 1.20.)
* Self leveling - Commands Sphero to level it's internal drive mechinism. (Added in firmware 1.20.)
* Set user hack mode - User hack mode enables ASCII shell commands.
* Quaternion streaming - API to support data streaming of quaternion orientation data. (Added in firmware 1.20.)
* Motion time out - Allows client code to set a time out to stop Sphero after the last roll command sent.
* User default color - Allows client code to set a user preferred color. This is the color used when Sphero first connects to a device and no color command is sent to it.
* Get power state - Client code can get the current power state and other information about the battery.
* Option flags - Client code can set options flags that effect some of Sphero's default behaviours.

#### New sample code

* Locator - Demonstrates the use of the new Locator API.
* MacroSample - Demonstrates creating macros in code, and sending them to Sphero.
* MacroLoader - Demonstrates loading macros made in MacroLab from your code.
* OptionsFlags - Demonstrates the use of the new options flag command.
* SelfLevel - Demonstrates how to use the self level command which levels the drive mechanism inside Sphero.
* StreamingAnimation - Demonstrates controlling an image of Sphero on a phone device's screen using accelerometer and yaw data streamed from Sphero.

## Fixes and such:

#### In the API

- Fix for collision detection parameters being sent in the wrong order. 
- The API will now set Sphero into a default state when closing a connect. This will turn off the back LED, data streaming, and collision detection. Also, Sphero is set to the users default color, and stabilization turned on.
- User can query event counts for acheivement events.
- Client code can get array of achievements data to present in native views.
- Multiplayer has new pause state and methods to pause and resume a game.
- Multiplayer improvements in handling players disconnecting.
- Multiplayer API can transition from started state back to lobby state.

#### In the samples

- HelloWorld - Handles disconnects and renconnects while the application is running.
- SensorStreaming - Updated to stream quaternion data. Plus, emulates infinite streaming by request a finite number of samples, and resends the data streaming command to continue the streaming. This fixes an issue caused when the application quits without turning off data streaming.
- CollisionDetection - Changed to use new methods that handle parameters correctly.



