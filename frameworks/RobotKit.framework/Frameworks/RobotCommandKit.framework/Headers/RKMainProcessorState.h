//
//  RKMainProcessorState.h
//  RobotCommandKit
//
//  Created by wes on 5/5/15.
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#ifndef RobotCommandKit_RKMainProcessorState_h
#define RobotCommandKit_RKMainProcessorState_h

// todo - move to robot & share with original SDK
/*! main processor state */
typedef NS_ENUM (uint8_t, RKMainProcessorState){
	RKMPState_Offline = 0,
	
	RKMPState_MainProcessorPowerOnRequested = 10,
	
	// Bluetooth Classic states start here.  > 10
	RKMPState_MainProcessorPowerOn = 11,
	
	/*! Never SET the state to Initializing, only use to compare*/
	RKMPState_Initializing = 15,
	
	RKMPState_JumpToMainAppRequested = 16,
	RKMPState_JumpToBootloaderRequested = 17,
	
	// Main Processor is online.
	RKMPState_JumpToBootloaderFailed = 20, /*! Failed to go to bootloader, and is still in the app. */
	RKMPState_InBootloader = 22,
	
	RKMPState_MainAppCorrupt = 91, /*! The robot reported a main app corrupt error, and is stuck in the bootloader. */
	
	RKMPState_InMainApp = 100, // in main app (9) : RKRobotOnline
	
	RKMPState_OfflineRequested = 101
};

#endif
