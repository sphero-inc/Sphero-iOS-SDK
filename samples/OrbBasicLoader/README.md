![logo](http://update.orbotix.com/developer/sphero-small.png)

# OrbBasicLoader

This sample demonstrates how to load and execute OrbBasic programs on Sphero. OrbBasic, like the macro executive, is another powerful resource that Sphero provides for autonomous behavior and integration with smart phone applications. It allows your to run a set of instructions on the ball which react to Sphero's sensors, without having to stream the data to the smartphone first. 

## The application 
This sample application uses the RKOrbBasicProgram class to do it's dirty work. When the application starts it loads orbBasic programs from the applications document directory creating RKOrbBasicProgram objects. Several sample programs are copied on first run into this directory, see the list below. Selecting a program in the table view will erase the previously selected program from Sphero. Once a program is selected pressing "Load" loads the program onto Sphero, and the program can now be executed, aborted, or erased. See the descriptions below for more details on these functions.

### Load
Loads the selected program onto Sphero. A RKOrbBasicProgram object will start listening to command responses to keep track of the state of the program. When the program is erased the object will stop listening to orbBasic command responses. This allows other RKOrbBasicProgram objects to load their programs and track their state.

### Execute
Excute sends a command to Sphero to start executing the currently loaded program. A RKOrbBasicProgram object will load the program if the program isn't already loaded. You can set the line that the program starts at with the startLineNumber property.

### Abort
Aborts the execution of the executing program which is useful for programs that loop infinitly.

### Erase 
Erases the current program from the storage on Sphero. A RKOrbBasicProgram object resets it state, and stops listening to responses to orbBasic commands.

## Sample Programs
On first run, the application will load default sample programs into the application's document directory. You can add your own programs using iTunes or from Xcode's Organizer window.

* **simple_assingment.orbbas** This program assigns two variables with a number and the first variable's square root. Then it uses the print statement which is returned to the application as a RKOrbBasicPrintMessage object.
* **syntax_error.orbbas** Demonstrates the error message returned in an asynchronous data packet when a syntax error is encountered.
* **program_error.orbbas** Demonstrates the program error message returned when performing a divide by zero.
* **data_example.orbbas** Demonstrates the use of the data and read statements. Due to a bug in the current firmware the read statement can only read one variable.
* **color_drive.orbbas** Demonstrates using the built in speed variable by changing the ball color as the ball is driven. You can switch to the Sphero application to drive Sphero and switch back to the sample application to abort execution.
* **toss_double-shake.orbbas** Demonstrates the use of the built in accelone an dshake variable.  The program waits for you to toss up Sphero and starts blinking the LED red. You double shake the ball to stop the program.