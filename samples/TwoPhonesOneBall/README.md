#Two Phones One Ball

This sample code demonstartes using 2 different devices to share control of 1 Sphero using the 
RKMultiplayer group of classes.  One of the devices should have a Sphero connected, this device
is referred to as 'host' in the code.  The other device should launch the app without a Sphero
connected and the two devices should find each other and connect once the app launches.  The two
devices can then pass driving control back and forth between each other by pressing the 'PASS'
button on the drive control screen.  The device that currently doesn't have drive control will
be shown a color picker allowing it to change the color of Sphero while the other device is
driving Sphero.