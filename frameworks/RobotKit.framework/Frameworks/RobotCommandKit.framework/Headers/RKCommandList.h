//
// Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

//PRIVATE: DON'T EXPORT HEADER INTO PUBLIC SDK

// commands that go with the core device id(0)
typedef NS_ENUM(uint8_t, RKCoreCommandIdType) {
    RKCoreCommandPing = 0x01,
    RKCoreCommandVersioning = 0x02,
    RKCoreCommandSetBluetoothName = 0x10,
    RKCoreCommandGetBluetoothInfo = 0x11,
    RKCoreCommandSetAutoReconnect = 0x12,
    RKCoreCommandGetAutoReconnect = 0x13,
    RKCoreCommandGetPowerState = 0x20,
    RKCoreCommandSetPowerNotification = 0x21,
    RKCoreCommandGoToSleep = 0x22,
    RKCoreCommandSetVoltageTripPoints = 0x24,
    RKCoreCommandSetInactivityTimeout = 0x25,
    RKCoreCommandGetFactoryConfigBlockCRC = 0x27,
    RKCoreCommandJumpToBootloader = 0x30,
    RKCoreCommandLevel1Diagnostic = 0x40,
    RKCoreCommandAssignTimeValue = 0x50,
    RKCoreCommandPollPacketTimes = 0x51
};

// commands that go with the bootloader device id(1)
typedef NS_ENUM(uint8_t, RKBootloaderCommandIdType) {
    RKBootloaderCommandBeginReflash = 0x02,
    RKBootloaderCommandHereIsPage = 0x03,
    RKBootloaderCommandJumpToMain = 0x04,
    RKBootloaderCommandIsPageBlank = 0x05,
    RKBootloaderCommandEraseUserConfig = 0x06
};

// commands that go with the sphero device id(2)
typedef NS_ENUM(uint8_t, RKSpheroCommandIdType) {
    RKSpheroCommandCalibrate = 0x01,
    RKSpheroCommandSetHeading = 0x01,
    RKSpheroCommandStabilization = 0x02,
    RKSpheroCommandRotationRate = 0x03,
    RKSpheroCommandSelfLevel = 0x09,
    RKSpheroCommandSetDataStreaming = 0x11,
    RKSpheroCommandConfigureCollisionDetection = 0x12,
    RKSpheroCommandConfigureLocator = 0x13,
    RKSpheroCommandRGBLEDOutput = 0x20,
    RKSpheroCommandBackLEDOutput = 0x21,
    RKSpheroCommandGetUserRGBLEDColor = 0x22,
    RKSpheroCommandRoll = 0x30,
    RKSpheroCommandBoost = 0x31,
    RKSpheroCommandRawMotorValues = 0x33,
    RKSpheroCommandSetMotionTimeout = 0x34,
    RKSpheroCommandSetOptionFlags = 0x35,
    RKSpheroCommandGetOptionFlags = 0x36,
    RKSpheroCommandSetNonPersistentOptionFlags = 0x37,
    RKSpheroCommandGetNonPersistentOptionFlags = 0x38,
    RKSpheroCommandGetConfigurationBlock = 0x40,
    RKSpheroCommandSetDeviceMode = 0x42,
    RKSpheroCommandSetConfigurationBlock = 0x43,
    RKSpheroCommandGetDeviceMode = 0x44,
    RKSpheroCommandSetFactoryDeviceMode = 0x45,
    RKSpheroCommandGetSSB = 0x46,
    RKSpheroCommandSetSSB = 0x47,
    RKSpheroCommandRefillBank = 0x48,
    RKSpheroCommandBuyConsumable = 0x49,
    RKSpheroCommandAddXp = 0x4C,
    RKSpheroCommandLevelUpAttribute = 0x4D,
    RKSpheroCommandRunMacro = 0x50,
    RKSpheroCommandSaveTempMacro = 0x51,
    RKSpheroCommandSaveMacro = 0x52,
    RKSpheroCommandSaveTempMacroChunk = 0x58,
    RKSpheroCommandInitMacroExecutive = 0x54,
    RKSpheroCommandAbortMacro = 0x55,
    RKSpheroCommandGetConfigBlock = 0x40,
    RKSpheroCommandOrbBasicEraseStorage = 0x60,
    RKSpheroCommandOrbBasicAppendFragment = 0x61,
    RKSpheroCommandOrbBasicExecute = 0x62,
    RKSpheroCommandOrbBasicAbort = 0x63,
    RKSpheroCommandOrbBasicCommitRamProgramToFlash = 0x65,
    RKSpheroCommandRemoveCores = 0x71,
    RKSpheroCommandSetSSBUnlockFlagsBlock = 0x72,
    RKSpheroCommandResetSoulBlock = 0x73,
    RKSpheroCommandReadOdometer = 0x75,
    RKSpheroCommandWritePersistentPage = 0x90
};

// commands for Sphero's soul
// TODO: change these values to the final values BKS
typedef NS_ENUM(uint8_t, RKSpheroSoulCommandIdType) {
    RKSpheroCommandReadSoulBlock    = 0xf0,
    RKSpheroCommandSoulAddXP        = 0xf1
};
