//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#ifndef RobotKit_RKTypes_h
#define RobotKit_RKTypes_h
/*! @file */

/*! Enumerated values for a robot's power state. */
typedef NS_ENUM(uint8_t,   RKBatteryPowerState ){
	RKBatteryPowerStateUnknown = 0,
	/*!
	 * The robot is charging. Note: an inductive charged robot will normally sleep in the charger,
	 * so you will not be able to issue a command to check the state.
	 */
	RKBatteryPowerStateCharging = 1,
	/*! The robot's battery is charged state. */
	RKBatteryPowerStateOK = 2,
	/*! The robot's battery is low and will soon need to be charged. */
	RKBatteryPowerStateLow = 3,
	/*! The robot's battery is critically low and the user needs to charge it immediatly. */
	RKBatteryPowerStateCritical = 4
};


/*! Charger state (introduced in BB-8) */
typedef NS_ENUM(NSUInteger, RKChargerState) {
	RKChargerState_Unknown = 0,
	RKChargerState_OutOfCharger = 1,
	RKChargerState_InCharger = 2
};


/*!
 Enumerated values for the storage type used for OrbBasic programs.
 */
typedef NS_ENUM(uint8_t,  RKOrbBasicStorageType ){
	/*! The OrbBasic program is stored into volatile memory, and will be erased when Sphero goes to sleep. */
	RKOrbBasicStorageTypeTemporary = 0,
	/* The OrbBasic program is stored into non-volatile memory, and will persiste until an erase command is sent. */
	RKOrbBasicStorageTypePersistent = 1
};


#endif
