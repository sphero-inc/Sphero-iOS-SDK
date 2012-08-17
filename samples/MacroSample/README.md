![logo](http://update.orbotix.com/developer/sphero-small.png)

# MacrosObjectiveC

This sample code demonstrates how to progromatticaly write a macros.


To create a macro,  


        RKMacroObject *macro = [RKMacroObject new];        

This call is implemented to create an object obtainting macro commands. 

To add new commands to the object:

        [macro addCommand: ...];

And to finally play the macro:

		[macro playMacro]; 



Simple Square, no repeat.

	-(IBAction)MacroSquare:(id)sender{
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Change Color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:0 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to blue
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:0]];
    //Sphero drives forward in the 90 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:90 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to yellow
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 180 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:180 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to red
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:0.0 blue:0.0 delay:0]];
    //Sphero drives forward in the 270 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:270 delay:robotDelay]];
    //Have Sphero to come to stop to make sharp turn
    [macro addCommand:[RKMCWaitUntilStop commandWithDelay:255]];
    //Change Color to white
    [macro addCommand:[RKMCRGB commandWithRed:1.0 green:1.0 blue:1.0 delay:0]];
    //Sphero comes to stop in the 0 angle
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:3000]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];
    }
    }

Roll Commands: Give a speed to travel, a direction in an 360 degree path, and a delay for the period of time of the action.


</br>

Colors Fade during action (Circle)
</br>

Slew(Fade) is a parrelell command
</br>

When Slew action is performed, either have it run 
parrallel to a roll command or a delay.
</br>

If the user was to include a blink color it would then end the slew abrumtly.

	-(IBAction)MacroColor:(id)sender{
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Sets loop from slider value
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    //Fade color to Blue
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:0.0 blue:1.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Fade color to Red
    [macro addCommand:[RKMCSlew commandWithRed:1.0 green:0.0 blue:0.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Fade color to Green
    [macro addCommand:[RKMCSlew commandWithRed:0.0 green:1.0 blue:0.0 delay:robotDelay]];
    //Add delay to allow Fade to complete before playing next fade
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Loop End
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];
    }

</br>

Macro Shape
</br>

Changes the Shape depending on the number of loops you 
include
</br>

Example: 4 loops makes a square
360 degrees / (4)= 90 degree turns     

	-(IBAction)MacroShape:(id)sender{
    //Create a new macro object to send to Sphero
     RKMacroObject *macro = [RKMacroObject new];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    //Change color to green
    [macro addCommand:[RKMCRGB commandWithRed:0.0 green:1.0 blue:0.0 delay:1000]];
    
    // Adding sequence of macro commands to make a full shape with
    // number of sides equal to robotLoop
    for(int i = 0; i < robotLoop; i++) {
        //Come to Stop
        [macro addCommand:[RKMCRGB commandWithRed:0.0 green:0.0 blue:1.0 delay:100]];

        [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:i*(360/robotLoop) delay:robotDelay]];
    }
    
	//    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];
	}


</br>
Figure 8 repeat
</br>
RotateOverTime is a parrelell command.
</br>
When a rotation action is performed, either have it run parrallel to a color command or a delay.
</br>
If the user was to include a drive command it would then end the rotation abrumtly.


	-(IBAction)MacroFigureEight:(id)sender{
    //Start with verb!!
    //Give Loop
    
    //Create a new macro object to send to Sphero
    RKMacroObject *macro = [RKMacroObject new];
    //Tell Robot to look forward and to start driving
    [macro addCommand:[RKMCRoll commandWithSpeed:robotSpeed heading:0 delay:2000]];
    //Start Loop
    [macro addCommand:[RKMCLoopFor commandWithRepeats:robotLoop]];
    ///Tell Robot to perform 1st turn in the postive direction.
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:360 delay:robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Rotate to pertform the 2nd turn in the negitive direction
    [macro addCommand:[RKMCRotateOverTime commandWithRotation:-360 delay:robotDelay]];
    //Add delay to allow the rotateovertime command to perform.
    [macro addCommand:[RKMCDelay commandWithDelay:robotDelay]];
    //Finsh loop
    [macro addCommand:[RKMCLoopEnd command]];
    //Come to stop
    [macro addCommand:[RKMCRoll commandWithSpeed:0.0 heading:0 delay:1000]];
    //Send full command dowm to Sphero to play
    [macro playMacro];
    //Release Macro
    [macro release];

	}
	