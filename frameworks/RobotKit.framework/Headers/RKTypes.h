//
//  RKTypes.h
//  RobotKit
//
//  Created by Brian Smith on 8/8/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#ifndef RobotKit_RKTypes_h
#define RobotKit_RKTypes_h
/*! @file */

/*! Enumerated values for a robot's power state. */
enum RKBatteryPowerState {
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

/*! Type definition for enumerated power states. */
typedef enum RKBatteryPowerState RKBatteryPowerState;

/*!
 Enumerated values for the storage type used for OrbBasic programs. 
 */
enum RKOrbBasicStorageType {
   /*! The OrbBasic program is stored into volatile memory, and will be erased when Sphero goes to sleep. */
         RKOrbBasicStorageTypeTemporary = 0,
   /* The OrbBasic program is stored into non-volatile memory, and will persiste until an erase command is sent. */
         RKOrbBasicStorageTypePersistent = 1
};

/*! Type definition for the storage type used for OrbBasic programs. */
typedef enum RKOrbBasicStorageType RKOrbBasicStorageType;


#endif
