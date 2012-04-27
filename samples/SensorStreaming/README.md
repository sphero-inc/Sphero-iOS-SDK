# Sensor Streaming

This sample code demonstrates how to connect to a Sphero and streaming the data onto the screen.
The connection is initiated by calling 

        [[RKRobotProvider sharedRobotProvider] openRobotConnection];        

This call into the RKRobotProvider singleton initiates the connection to a Sphero. Once the connection is opened and communications a verified ``RKDeviceConnectionOnlineNotification`` is posted for success, and ``RKDeviceConnectionOfflineNotification`` is posted on failure. In the handler for the ``RKDeviceConnectionOnlineNotification`` notification, the `toggleLED` method is called which starts blinking Sphero's RGB LED blue.






When the application exits the connection is closed with the following line of code.

    [[RKRobotProvider sharedRobotProvider] closeRobotConnection];





