//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

// PRIVATE TO THE SOURCE. NOT FOR THE PUBLIC SDK.

typedef NS_ENUM(uint8_t, RKBroadcastPacket){
   RKAsyncPacketPowerNotifications = 0x01,
   RKAsyncPacketLevel1DiagnosticResponse = 0x02,
   RKAsyncPacketSensorDataStreaming = 0x03,
   RKAsyncPacketConfigBlockContents = 0x04,
   RKAsyncPacketPreSleepWarning = 0x05,
   RKAsyncPacketMacroEmitMarker = 0x06,
   RKAsyncPacketCollisionDetected = 0x07,
   RKAsyncPacketOrbBasicPrint = 0x08,
   RKAsyncPacketOrbBasicErrorASCII = 0x09,
   RKAsyncPacketOrbBasicErrorBinary = 0x0A,
   RKAsyncPacketSelfLevelComplete = 0x0B,
   RKAsyncPacketGyroRangeExceeded = 0x0C,
   RKAsyncPacketSoulDataResponse = 0x0D,
   RKAsyncPacketSoulLevelUpNotification = 0x0E,
   RKAsyncPacketSoulShieldNotification = 0x0F,
   RKAsyncPacketBoostNotification = 0x11,
    
    // TODO: Update to final values.
    RKAsyncPacketSoulBlockData = 0x20,
    RKAsyncPacketXPUpdateEvent = 0x21
};