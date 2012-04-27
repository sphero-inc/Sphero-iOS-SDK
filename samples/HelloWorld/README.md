# HelloWorld

This sample code demonstrates how to connect to a Sphero and blink it's RGB LED blue. Also, the code sample is the bases for the application created in the Quick Start Guide. 

The connection is initiated by calling 

        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        

This call into the RKRobotProvider singleton initiates the connection to a Sphero. Once the connection is opened and communications a verified ``RKDeviceConnectionOnlineNotification`` is posted for success, and ``RKDeviceConnectionOfflineNotification`` is posted on failure. In the handler for the ``RKDeviceConnectionOnlineNotification`` notification, the `toggleLED` method is called which starts blinking Sphero's RGB LED blue.

The RGB LED is turned off using the following line of code where a 0.0 value sets the LED color component's brightness off.

        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:0.0];

The RGB LED sets the blue LED component to full brightness with following line.

        [RKRGBLEDOutputCommand sendCommandWithRed:0.0 green:0.0 blue:1.0];

RKRGBLEDOutputCommand is a subclass of RKDeviceCommand whose subclasses are used to post a command to Sphero by using RKDeviceMessenger. The `[RKRGBLEDOutputCommand sendCommandWithRed: green: blue:]` is a convenience method that creates the object and posts it RKDeviceMessenger. 

When the application exits the connection is closed with the following line of code.

    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];





