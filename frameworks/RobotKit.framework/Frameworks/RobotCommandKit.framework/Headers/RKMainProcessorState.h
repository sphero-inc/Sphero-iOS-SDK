typedef NS_ENUM (uint8_t, RKMainProcessorState){
	RKMPState_Offline = 0,
	RKMPState_MainProcessorPowerOnRequested = 10,
	RKMPState_MainProcessorPowerOn = 11,
	RKMPState_Initializing = 15,
	RKMPState_JumpToMainAppRequested = 16,
	RKMPState_JumpToBootloaderRequested = 17,
	RKMPState_JumpToBootloaderFailed = 20,
	RKMPState_InBootloader = 22,
	RKMPState_MainAppCorrupt = 91,
	RKMPState_InMainApp = 100,
	RKMPState_OfflineRequested = 101
};