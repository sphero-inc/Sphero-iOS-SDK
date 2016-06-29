#ifndef RobotKit_RKTypes_h
#define RobotKit_RKTypes_h

typedef NS_ENUM(uint8_t, RKBatteryPowerState) {
	RKBatteryPowerStateUnknown = 0,
	RKBatteryPowerStateCharging = 1,
	RKBatteryPowerStateOK = 2,
	RKBatteryPowerStateLow = 3,
	RKBatteryPowerStateCritical = 4
};

typedef NS_ENUM(NSUInteger, RKChargerState) {
	RKChargerState_Unknown = 0,
	RKChargerState_OutOfCharger = 1,
	RKChargerState_InCharger = 2
};

typedef NS_ENUM(uint8_t, RKOrbBasicStorageType) {
	RKOrbBasicStorageTypeTemporary = 0,
	RKOrbBasicStorageTypePersistent = 1
};

typedef NS_OPTIONS(uint64_t, RKDataStreamingMask) {
    RKDataStreamingMaskOff = 0x0000000000000000,
    RKDataStreamingMaskLeftMotorBackEMFFiltered = 0x0000000000000060,
    RKDataStreamingMaskRightMotorBackEMFFiltered = 0x0000000000000060,
    RKDataStreamingMaskMagnetometerZFiltered = 0x0000000000000080,
    RKDataStreamingMaskMagnetometerYFiltered = 0x0000000000000100,
    RKDataStreamingMaskMagnetometerXFiltered = 0x0000000000000200,
    RKDataStreamingMaskGyroZFiltered = 0x0000000000000400,
    RKDataStreamingMaskGyroYFiltered = 0x0000000000000800,
    RKDataStreamingMaskGyroXFiltered = 0x0000000000001000,
    RKDataStreamingMaskAccelerometerZFiltered = 0x0000000000002000,
    RKDataStreamingMaskAccelerometerYFiltered = 0x0000000000004000,
    RKDataStreamingMaskAccelerometerXFiltered = 0x0000000000008000,
    RKDataStreamingMaskIMUYawAngleFiltered = 0x0000000000010000,
    RKDataStreamingMaskIMURollAngleFiltered = 0x0000000000020000,
    RKDataStreamingMaskIMUPitchAngleFiltered = 0x0000000000040000,
    RKDataStreamingMaskLeftMotorBackEMFRaw =  0x0000000000600000,
    RKDataStreamingMaskRightMotorBackEMFRaw = 0x0000000000600000,
    RKDataStreamingMaskMotorPWM =  0x00100000 | 0x00080000,
    RKDataStreamingMaskMagnetometer = 0x0000000002000000,
    RKDataStreamingMaskGyroZRaw = 0x0000000004000000,
    RKDataStreamingMaskGyroYRaw = 0x0000000008000000,
    RKDataStreamingMaskGyroXRaw = 0x0000000010000000,
    RKDataStreamingMaskAccelerometerZRaw = 0x0000000020000000,
    RKDataStreamingMaskAccelerometerYRaw = 0x0000000040000000,
    RKDataStreamingMaskAccelerometerXRaw = 0x0000000080000000,
    RKDataStreamingMaskAccelerometerRaw =  0x00000000E0000000,
    RKDataStreamingMaskQuaternion0 = 0x8000000000000000,
    RKDataStreamingMaskQuaternion1 = 0x4000000000000000,
    RKDataStreamingMaskQuaternion2 = 0x2000000000000000,
    RKDataStreamingMaskQuaternion3 = 0x1000000000000000,
    RKDataStreamingMaskLocatorX = 0x0800000000000000,
    RKDataStreamingMaskLocatorY = 0x0400000000000000,
    RKDataStreamingMaskVelocityX = 0x0100000000000000,
    RKDataStreamingMaskVelocityY = 0x0080000000000000,
    RKDataStreamingMaskGyroFilteredAll = 0x0000000000001C00,
    RKDataStreamingMaskIMUAnglesFilteredAll = 0x0000000000070000,
    RKDataStreamingMaskAccelerometerFilteredAll = 0x000000000000E000,
    RKDataStreamingMaskLocatorAll = 0x0D80000000000000,
    RKDataStreamingMaskQuaternionAll = 0xF000000000000000
};

#endif