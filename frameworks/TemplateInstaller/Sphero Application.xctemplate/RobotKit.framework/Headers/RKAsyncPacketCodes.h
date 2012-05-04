//
//  RKAsyncPacketCodes.h
//  RobotKit
//
//  Created by Brian Smith on 7/7/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

// PRIVATE TO THE SOURCE. NOT FOR THE PUBLIC SDK.

enum {
    RKAsyncPacketPowerNotifications         = 0x01,
    RKAsyncPacketLevel1DiagnosticResponse   = 0x02,
    RKAsyncPacketSensorDataStreaming        = 0x03,
    RKAsyncPacketConfigBlockContents        = 0x04,
    RKAsyncPacketPreSleepWarning            = 0x05,
    RKAsyncPacketMacroEmitMarker            = 0x06,
    RKAsyncPacketCollisionDetected          = 0x07,
    RKAsyncPacketOrbBasicPrint              = 0x08,
    RKAsyncPacketOrbBasicErrorASCII         = 0x09,
    RKAsyncPacketOrbBasicErrorBinary        = 0x0A
};