//
//  Copyright (c) 2014 orbotix. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>
#import <RobotLanguageKit/RobotLanguageKit.h>
#import "RKDriveable.h"
#import "RKSensorControl.h"


@interface RKConvenienceRobot : NSObject <RKDriveable>

@property (strong, nonatomic) id<RKRobotBase> robot;
@property (strong, nonatomic) RKSensorControl *sensorControl;
@property (strong, nonatomic) RKVersioningResponse *lastVersioning;

@property (strong, nonatomic, readonly) RKMacroPlayer* macroPlayer;
@property (nonatomic, assign) float currentHeading;


+(id) convenienceWithRobot:(id<RKRobotBase>) robotBase;

/*! */
-(id) initWithRobot:(id<RKRobotBase>) robot;

/*! */
-(void) sendCommand:(RKDeviceCommand*) cmd;

/*! This command puts Sphero to sleep immediately. */
-(void) sleep;

/*! This will disconnect the robot. Ollie will go to sleep before disconnect. Sphero will disconnect immediately. */
-(void) disconnect;

-(BOOL) isConnected;

-(BOOL) isOnline;

-(NSString *)name;


#pragma mark - Drive

/*! */
-(void) driveWithHeading:(float) heading andVelocity:(float) velocity;

/*! */
-(void) driveWithHeading:(float) heading andVelocity:(float) velocity andReverse:(bool) reverse;

/*! */
-(void) stop;

/*! This turns on or off the internal stabilization of Sphero, in which the IMU is used to match the robot's orientation to its various set points. Stabilization is enabled by default when Sphero powers up. You will want to disable stabilization when using a Robot as an external input controller or even to save battery power during testing that doesn't involve movement (orbBasic, etc.)
 
 This command does not set motion timeout timer so control system will remain on until turned off or a command is received that sets the motion timeout timer.
 
 An error is returned if the sensor network is dead; without sensors the IMU won't operate and thus there is no feedback to control stabilization.*/
-(void) enableStabilization:(BOOL) on;

/*! */
-(void) setZeroHeading; // calibrate


#pragma mark - LEDS

/*! */
-(void) setLEDWithRed:(float) redVal green:(float) greenVal blue:(float) blueVal;

/*! */
-(void) setLEDDefaultWithRed:(float)redVal green:(float)greenVal blue:(float)blueVal;

/*! */
-(void) setBackLEDBrightness:(float) brightness;

#pragma mark - Sensors

/*! Sphero robots contain powerful analysis functions to filter accelerometer data in order to detect collisions. Because this is a great example of a high-level concept that humans excel and – but robots do not – a number of parameters control the behavior. When a collision is detected an asynchronous message is generated. */
-(void) enableCollisions:(BOOL)enable;

/*! Sphero Robots provide real-time location data in the form of (X,Y) coordinates on the ground plane through the streaming interface. Note that the location will be inaccurate if the robot slips or drifts while navigating.  When a Robot wakes up it has coordinates (0,0) and heading 0, which corresponds to facing down the positive Y-axis with the positive X-axis to your right. This command allows you to move Sphero to a new location and change the alignment of locator coordinates with IMU headings. */
-(void) enableLocator:(BOOL)enable;

/*! Sphero supports asynchronous data streaming of important information from the sensors, IMU, and control system. The Set Data Streaming command determines what information Sphero will report, how often that information will be sampled, */
-(void) enableSensors:(RKDataStreamingMask)mask atStreamingRate:(RKStreamingRate)hz;

/*! */
-(void) disableSensors;


#pragma mark - Macros

-(void) playMacro:(RKMacroObject*) macro;
/*!
 This attempts to execute the specified macro. Macro IDs are organized into groups: 01 – 31 are System Macros, that is, they are compiled into the Main Application. As such they are always available to be run and cannot be deleted. Macro IDs 32 – 253 are User Macros that are downloaded and persistently stored. They can be deleted in total. Macro ID 255 is a special user macro called the Temporary Macro as it is held in RAM for execution. Macro ID 254 is also a special user macro called the Stream Macro that doesn't require this call to begin execution.
 
 This command will fail if there is currently an executing macro or the specified ID Code isn't found. In the case of the former, send an abort command first. */
-(void) macroRunAtId:(uint8_t) identifier;

/*! */
-(void) macroAbort;

-(void) macroSaveTemporary:(NSData*) data;

//-(RKMacroPlayer) getMacroPlayer;



#pragma mark - OrbBasic - unimplemented

/*! This erases any existing program in the specified storage area. Specify 00h for the temporary RAM buffer or 01h for the persistent storage area.*/
-(void) resetOrbBasicMemory;


/*! Sending an orbBasic program to Sphero involves appending blocks of text to existing ones in the specified storage area (00h for RAM, 01h for persistent). Complete lines are not required. A line begins with a decimal line number followed by a space and is terminated with a <LF>. See the orbBasic Interpreter document for complete information.
 Possible error responses would be ORBOTIX_RSP_CODE_EPARAM if an illegal storage area is specified or ORBOTIX_RSP_CODE_EEXEC if the specified storage area is full.*/
-(void) appendOrbBasicProgram:(NSData*) data;


/*! This attempts to run a program in the specified storage area beginning at the specified line number. This command will fail if there is already an orbBasic program executing. */
-(void) executeOrbBasicProgramAtLine:(uint16_t) lineNumber;


/*! This takes the place of the typical user console in orbBasic and allows a user to answer an input request. If there is no pending input request when this API command is sent, the supplied value is ignored without error. Refer to the orbBasic language document for further information.
 */
//-(void) submitOrbBasicInput:(int32_t) input;


/*! Aborts execution of any currently running orbBasic program. */
-(void) abortOrbBasic;


#pragma mark - Responses

/*! add a Response Observer for both command responses and async messages */
-(void) addResponseObserver:(__weak id<RKResponseObserver>) observer;

/*! remove a response observer */
-(void) removeResponseObserver:(id<RKResponseObserver>) observer;


#pragma mark - Raw Motors Unimplemented

-(void) setRawMotorsLeftMode:(RKRawMotorMode) leftMode
                   leftPower:(uint8_t) leftPower
                   rightMode:(RKRawMotorMode) rightMode
                  rightPower:(uint8_t) rightPower;

@end
