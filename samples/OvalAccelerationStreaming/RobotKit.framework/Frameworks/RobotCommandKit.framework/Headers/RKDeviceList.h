/*
 *  RKDeviceList.h
 *  RobotKit
 *
 *  Created by Brian Smith on 5/31/11.
 *  Copyright 2011 Orbotix Inc. All rights reserved.
 *
 */

typedef NS_ENUM (uint8_t, RKDeviceIdType) {
   RKDeviceIdCore = 0x00,
   RKDeviceIdBootloader = 0x01,
   RKDeviceIdSphero = 0x02,
   RKDeviceIdSpheroSoul = 0x03
   // TODO: change this to the final value BKS !!!
};