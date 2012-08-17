![logo](http://update.orbotix.com/developer/sphero-small.png)

# Temporary Macro Sample

Adding MacroLab macros to app
importing the files out of MacroLab:

Follow the tutorial below to get the file attached to an E-mail to your own address.

http://forum.gosphero.com/showthread...5-Share-Macros

Placing Files in Xcode:

Drag file into Project
Click on file and click on the page icon for "show file inspector"
Add as a Target Membership

Import MacroCommands and AbortMacro from RobotLibrary:
</br>

Calling the files in .m:

Code:
  
    NSString *file = [[NSBundle mainBundle] pathForResource:@"colors" ofType:@"sphero"];
    NSData *data = [NSData dataWithContentsOfFile:file];


    [RKSaveTemporaryMacroCommand sendCommandWithMacro:data flags:RKMacroFlagMotorControl];
    [RKRunMacroCommand sendCommandWithId:255];

</br>
Stopping all actions:</br>
Code:

    [RKAbortMacroCommand sendCommand];
    [RKStabilizationCommand sendCommandWithState:	(RKStabilizationStateOn)];

