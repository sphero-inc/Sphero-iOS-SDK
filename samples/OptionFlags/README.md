positive![logo](http://update.orbotix.com/developer/sphero-small.png)

# Option Flags

	Note: These commands only work on Sphero's with Firmware 1.20 or greater 

Option flags are settings that stay with Sphero even after it goes through power cycles.  There are currently 5 different settings you can change.  These are:

1.  Prevent Sleep In Charger
2.  Enable Vector Drive
3.  Disable Self Level In Charger
4.  Tail Light Always On
5.  Enable Motion Timeout

By default, your Sphero only has vector drive enabled.  

	Warning: If you are going to change any of these settings, please make sure to set them back to the default upon your app closing
	
## Get Current Option Flags	
	
To get the current state of the option flags, you must register a response callback when the robot comes online.  Then, you call the command to request the option flags.  This is done with the following code:

	- (void)handleRobotOnline {

	    if(!robotOnline) {

	        [[RKDeviceMessenger sharedMessenger] addResponseObserver:self selector:@selector(handleResponse:)];

	        [RKGetOptionFlagsCommand sendCommand];
	    }
	    robotOnline = YES;
	}	
	
Now you will be notified by the handleResponse method when you receive a response from Sphero.  Retrieve the option flags from the following callback:

	-(void)handleResponse:(RKDeviceResponse *)response {
	
	    // Only respond to get option flags responses
	    if( [response isKindOfClass:[RKGetOptionFlagsResponse class]] ) {
	        RKGetOptionFlagsResponse* optionFlagsResponse = (RKGetOptionFlagsResponse*) response;
			
	        // Display the current option flags as true/false labels
	        self.bit0Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsPreventSleepInCharger]) ? @"true":@"false";
	        
	        self.bit1Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsEnableVectorDrive]) ? @"true":@"false";
	        
	        self.bit2Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsDisableSelfLevelInCharger]) ? @"true":@"false";
	        
	        self.bit3Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsTailLightAlwaysOn]) ? @"true":@"false";
	        
	        self.bit4Label.text = ([optionFlagsResponse isSetWithOptionFlag:RKGetOptionFlagsEnableMotionTimeout]) ? @"true":@"false";
	    }
	}
	
Here we are displaying the state of each option flag in a text field with either "false" (off) or "true" (on).

## Set Option Flags

You can change the value of the option flags by sending a bitwise mask to Sphero with the *RKSetOptionFlagsCommand*.  This is done in code by:

    RKGetOptionFlagsMask optionFlags = 0;
    
    // Add prevent sleep in charger flag value
    if( bit0Switch.isOn ) optionFlags |= RKGetOptionFlagsPreventSleepInCharger;
    
    // Add enable vector drive flag value
    if( bit1Switch.isOn ) optionFlags |= RKGetOptionFlagsEnableVectorDrive;
    
    // Add disable self level in charger flag level
    if( bit2Switch.isOn) optionFlags |= RKGetOptionFlagsDisableSelfLevelInCharger;
    
    // Add tail light always on flag
    if( bit3Switch.isOn) optionFlags |= RKGetOptionFlagsTailLightAlwaysOn;
    
    // Add enable motion timeout flag
    if( bit4Switch.isOn) optionFlags |= RKGetOptionFlagsEnableMotionTimeout;
    
    // Send command to set option flags
    [RKSetOptionFlagsCommand sendCommandWithOptionFlags:optionFlags];
    
Here we set the value of each flag to the value of a UISwitch.  We then send the command to ball to set the option flags.
## Questions

For questions, please visit our developer's forum at [http://forum.gosphero.com/](http://forum.gosphero.com/)

	  