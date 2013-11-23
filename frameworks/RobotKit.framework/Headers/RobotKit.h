//
//  RobotKit.h
//  RobotKit
//
//  Copyright 2010 Orbotix Inc. All rights reserved.
//

#include <RobotKit/RKTypes.h>

#import <RobotKit/RKMath.h>
#import <RobotKit/RKAccelerometerFilter.h>

#import <RobotKit/RKDriveControl.h>
#import <RobotKit/RKDeviceConnection.h>
#import <RobotKit/RKRobot.h>
#import <RobotKit/RKRobotControl.h>
#import <RobotKit/RKRobotProvider.h>
#import <RobotKit/RKJoyStickDriveAlgorithm.h>
#import <RobotKit/RKTiltDriveAlgorithm.h>

#import <RobotKit/RKResponseCodes.h>
#import <RobotKit/RKDeviceMessenger.h>

// Commands
//// core
#import <RobotKit/RKPingCommand.h>
#import <RobotKit/RKVersioningCommand.h>
#import <RobotKit/RKGoToSleepCommand.h>
#import <RobotKit/RKSetUserHackModeCommand.h>
#import <RobotKit/RKGetBluetoothInfoCommand.h>
#import <RobotKit/RKGetPowerStateCommand.h>
#import <RobotKit/RKPollPacketTimesCommand.h>
#import <RobotKit/RKSetPowerNotificationCommand.h>
#import <RobotKit/RKSetInactivityTimeoutCommand.h>
#import <RobotKit/RKSetAutoReconnectCommand.h>
#import <RobotKit/RKGetAutoReconnectCommand.h>
//// bootloader
#import <RobotKit/RKJumpToBootloaderCommand.h>
#import <RobotKit/RKJumpToMainAppCommand.h>
//// sphero
#import <RobotKit/RKCalibrateCommand.h>
#import <RobotKit/RKSetHeadingCommand.h>
#import <RobotKit/RKRGBLEDOutputCommand.h>
#import <RobotKit/RKBackLEDOutputCommand.h>
#import <RobotKit/RKRollCommand.h>
#import <RobotKit/RKRotationRateCommand.h>
#import <RobotKit/RKSetDataStreamingCommand.h>
#import <RobotKit/RKStabilizationCommand.h>
#import <RobotKit/RKRawMotorValuesCommand.h>
#import <RobotKit/RKConfigureCollisionDetectionCommand.h>
#import <RobotKit/RKGetDeviceModeCommand.h>
#import <RobotKit/RKConfigureLocatorCommand.h>
#import <RobotKit/RKSelfLevelCommand.h>
#import <RobotKit/RKSetMotionTimeoutCommand.h>
#import <RobotKit/RKGetOptionFlagsCommand.h>
#import <RobotKit/RKSetOptionFlagsCommand.h>
#if defined (SRCLIBRARY)
#import <RobotKit/orbBasic/RKOrbBasicEraseStorageCommand.h>
#import <RobotKit/orbBasic/RKOrbBasicAppendFragmentCommand.h>
#import <RobotKit/orbBasic/RKOrbBasicExecuteCommand.h>
#import <RobotKit/orbBasic/RKOrbBasicAbortCommand.h>
#else
#import <RobotKit/RKOrbBasicEraseStorageCommand.h>
#import <RobotKit/RKOrbBasicAppendFragmentCommand.h>
#import <RobotKit/RKOrbBasicExecuteCommand.h>
#import <RobotKit/RKOrbBasicAbortCommand.h>
#endif

// Responses
//// core
#import <RobotKit/RKPingResponse.h>
#import <RobotKit/RKVersioningResponse.h>
#import <RobotKit/RKGetBluetoothInfoResponse.h>
#import <RobotKit/RKGetPowerStateResponse.h>
#import <RobotKit/RKPollPacketTimesResponse.h>
#import <RobotKit/RKSetPowerNotificationResponse.h>
#import <RobotKit/RKSetInactivityTimeoutResponse.h>
#import <RobotKit/RKSetAutoReconnectResponse.h>
#import <RobotKit/RKGetAutoReconnectResponse.h>
//// bootloader
#import <RobotKit/RKJumpToBootloaderResponse.h>
#import <RobotKit/RKJumpToMainAppResponse.h>
//// sphero
#import <RobotKit/RKCalibrateResponse.h>
#import <RobotKit/RKSetHeadingResponse.h>
#import <RobotKit/RKRGBLEDOutputResponse.h>
#import <RobotKit/RKBackLEDOutputResponse.h>
#import <RobotKit/RKRollResponse.h>
#import <RobotKit/RKSetUserHackModeResponse.h>
#import <RobotKit/RKRotationRateResponse.h>
#import <RobotKit/RKSetDataStreamingResponse.h>
#import <RobotKit/RKStabilizationResponse.h>
#import <RobotKit/RKRawMotorValuesResponse.h>
#import <RobotKit/RKGoToSleepResponse.h>
#import <RobotKit/RKConfigureCollisionDetectionResponse.h>
#import <RobotKit/RKGetDeviceModeResponse.h>
#import <RobotKit/RKConfigureLocatorResponse.h>
#import <RobotKit/RKSelfLevelResponse.h>
#import <RobotKit/RKSetMotionTimeoutResponse.h>
#import <RobotKit/RKGetOptionFlagsResponse.h>
#import <RobotKit/RKSetOptionFlagsResponse.h>
#if defined (SRCLIBRARY)
#import <RobotKit/orbBasic/RKOrbBasicEraseStorageResponse.h>
#import <RobotKit/orbBasic/RKOrbBasicAppendFragmentResponse.h>
#import <RobotKit/orbBasic/RKOrbBasicExecuteResponse.h>
#import <RobotKit/orbBasic/RKOrbBasicAbortResponse.h>
#else
#import <RobotKit/RKOrbBasicEraseStorageResponse.h>
#import <RobotKit/RKOrbBasicAppendFragmentResponse.h>
#import <RobotKit/RKOrbBasicExecuteResponse.h>
#import <RobotKit/RKOrbBasicAbortResponse.h>
#endif


// Async Data
#import <RobotKit/RKDeviceAsyncData.h>
#import <RobotKit/RKCollisionDetectedAsyncData.h>
#import <RobotKit/RKSelfLevelCompleteAsyncData.h>
#import <RobotKit/RKDeviceSensorsAsyncData.h>
#import <RobotKit/RKDeviceSensorsData.h>
#import <RobotKit/RKAccelerometerData.h>
#import <RobotKit/RKMagnetometerData.h>
#import <RobotKit/RKAttitudeData.h>
#import <RobotKit/RKGyroData.h>
#import <RobotKit/RKBackEMFData.h>
#import <RobotKit/RKLocatorData.h>
#import <RobotKit/RKQuaternionData.h>
#import <RobotKit/RKSleepNotificationAsyncData.h>
#import <RobotKit/RKPowerNotificationAsyncData.h>
#if defined (SRCLIBRARY)
#import <RobotKit/orbBasic/RKOrbBasicPrintMessage.h>
#import <RobotKit/orbBasic/RKOrbBasicErrorASCII.h>
#import <RobotKit/orbBasic/RKOrbBasicErrorBinary.h>
#else
#import <RobotKit/RKOrbBasicPrintMessage.h>
#import <RobotKit/RKOrbBasicErrorASCII.h>
#import <RobotKit/RKOrbBasicErrorBinary.h>
#endif

// Achievements
#import <RobotKit/RKAchievement.h>
#import <RobotKit/RKSpheroWorldAuth.h>


// Multiplayer
#if defined (SRCLIBRARY)
#import <RobotKit/Multiplayer/RKMultiplayer.h>
#import <RobotKit/Multiplayer/RKRemotePlayer.h>
#import <RobotKit/Multiplayer/RKRemoteRobot.h>
#import <RobotKit/Multiplayer/RKRemoteSphero.h>
#import <RobotKit/Multiplayer/RKMultiplayerGame.h>
#else
#import <RobotKit/RKMultiplayer.h>
#import <RobotKit/RKRemotePlayer.h>
#import <RobotKit/RKRemoteRobot.h>
#import <RobotKit/RKRemoteSphero.h>
#import <RobotKit/RKMultiplayerGame.h>
#endif

// Macros
#if defined (SRCLIBRARY)
#import <RobotKit/Macro/RKMacroObject.h>
#import <RobotKit/RKInitMacroExecutiveCommand.h>
#import <RobotKit/RKSaveTemporaryMacroChunkCommand.h>
#import <RobotKit/RKInitMacroExecutiveResponse.h>
#import <RobotKit/RKSaveTemporaryMacroChunkResponse.h>
#import <RobotKit/Macro/RKSaveMacroCommand.h>
#import <Robotkit/Macro/RKRunMacroCommand.h>
#import <RobotKit/Macro/RKRunMacroResponse.h>
#import <RobotKit/Macro/RKAbortMacroCommand.h>
#import <RobotKit/Macro/RKAbortMacroResponse.h>
#else
#import <RobotKit/RKMacroObject.h>
#import <RobotKit/RKInitMacroExecutiveCommand.h>
#import <RobotKit/RKSaveTemporaryMacroChunkCommand.h>
#import <RobotKit/RKInitMacroExecutiveResponse.h>
#import <RobotKit/RKSaveTemporaryMacroChunkResponse.h>
#import <RobotKit/RKSaveMacroCommand.h>
#import <Robotkit/RKRunMacroCommand.h>
#import <RobotKit/RKRunMacroResponse.h>
#import <RobotKit/RKAbortMacroCommand.h>
#import <RobotKit/RKAbortMacroResponse.h>
#endif

// Messages
#if defined (SRCLIBRARY)
#import <RobotKit/RKDeviceMessage.h>
#import <RobotKit/RKDeviceMessageEncoder.h>
#import <RobotKit/RKDeviceMessageDecoder.h>
#import <RobotKit/RKDeviceNotification.h>
#import <RobotKit/RKDeviceMessageCoding.h>
#else
#import <RobotKit/RKDeviceMessage.h>
#import <RobotKit/RKDeviceMessageEncoder.h>
#import <RobotKit/RKDeviceMessageDecoder.h>
#import <RobotKit/RKDeviceNotification.h>
#import <RobotKit/RKDeviceMessageCoding.h>
#endif

// orbBasic
#if defined (SRCLIBRARY)
#import <RobotKit/orbBasic/RKOrbBasicProgram.h>
#else
#import <RobotKit/RKOrbBasicProgram.h>
#endif


