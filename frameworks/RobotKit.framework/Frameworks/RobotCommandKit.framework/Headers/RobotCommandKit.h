#import <Foundation/Foundation.h>

FOUNDATION_EXPORT double RobotCommandKitVersionNumber;

FOUNDATION_EXPORT const unsigned char RobotCommandKitVersionString[];

#import <RobotCommandKit/RobotCommandKit-Prefix.pch>
#import <RobotCommandKit/RKLinkDelegate.h>
#import <RobotCommandKit/RKRobotBase.h>
#import <RobotCommandKit/RKDiscoveryAgent.h>
#import <RobotCommandKit/RKAppUtils.h>
#import <RobotCommandKit/RKBuildDescriptors.h>

#pragma mark - all robots
#import <RobotCommandKit/RKRobotNotification.h>
#import <RobotCommandKit/NSData+Extensions.h>

// Drive algorithms
#import <RobotCommandKit/RKDriveAlgorithm.h>
#import <RobotCommandKit/RKJoyStickDriveAlgorithm.h>

// Common
#import <RobotCommandKit/RKByteCommand.h>
#import <RobotCommandKit/RKByteResponse.h>
#import <RobotCommandKit/RKByteAsyncMessage.h>
#import <RobotCommandKit/RKDeviceMessage.h>
#import <RobotCommandKit/RKDeviceCommand.h>
#import <RobotCommandKit/RKAsyncFactory.h>
#import <RobotCommandKit/RKResponseFactory.h>

#import <RobotCommandKit/RKAsyncMessage.h>
#import <RobotCommandKit/RKAsyncId.h>
#import <RobotCommandKit/RKDeviceResponse.h>
#import <RobotCommandKit/RKResponseCodes.h>
#import <RobotCommandKit/RKMainProcessorState.h>
#import <RobotCommandKit/RKLastDataStreamingDataTracker.h>
#import <RobotCommandKit/RKStats.h>
#import <RobotCommandKit/RKFlashWritingCommandDetector.h>
#import <RobotCommandKit/RKRollingQueue.h>

// Session
#import <RobotCommandKit/RKSession.h>
#import <RobotCommandKit/RKV1Session.h>
#import <RobotCommandKit/RKV2Session.h>

//// Core
#import <RobotCommandKit/RKGetAutoReconnectCommand.h>
#import <RobotCommandKit/RKGetBluetoothInfoCommand.h>
#import <RobotCommandKit/RKGetPowerStateCommand.h>
#import <RobotCommandKit/RKPingCommand.h>
#import <RobotCommandKit/RKSetAutoReconnectCommand.h>
#import <RobotCommandKit/RKSetBluetoothNameCommand.h>
#import <RobotCommandKit/RKSetInactivityTimeoutCommand.h>
#import <RobotCommandKit/RKSetPowerNotificationCommand.h>
#import <RobotCommandKit/RKVersioningCommand.h>
#import <RobotCommandKit/RKJumpToBootloaderCommand.h>
#import <RobotCommandKit/RKGoToSleepCommand.h>
#import <RobotCommandKit/RKGetChargerStateCommand.h>

//// Bootloader
#import <RobotCommandKit/RKJumpToMainAppCommand.h>

#pragma mark - Commands
#import <RobotCommandKit/RKRollCommand.h>
#import <RobotCommandKit/RKGetChassisIdCommand.h>
#import <RobotCommandKit/RKStabilizationCommand.h>
#import <RobotCommandKit/RKSetHeadingCommand.h>
#import <RobotCommandKit/RKRotationRateCommand.h>
#import <RobotCommandKit/RKSetDataStreamingCommand.h>
#import <RobotCommandKit/RKRawMotorValuesCommand.h>
#import <RobotCommandKit/RKConfigureCollisionDetectionCommand.h>
#import <RobotCommandKit/RKSetUserHackModeCommand.h>
#import <RobotCommandKit/RKGetDeviceModeCommand.h>
#import <RobotCommandKit/RKConfigureLocatorCommand.h>
#import <RobotCommandKit/RKSelfLevelCommand.h>
#import <RobotCommandKit/RKSetMotionTimeoutCommand.h>
#import <RobotCommandKit/RKSetOptionFlagsCommand.h>
#import <RobotCommandKit/RKGetOptionFlagsCommand.h>
#import <RobotCommandKit/RKSetNonPersistentOptionFlagsCommand.h>
#import <RobotCommandKit/RKGetNonPersistentOptionFlagsCommand.h>
#import <RobotCommandKit/RKSetFactoryDeviceModeCommand.h>
#import <RobotCommandKit/RKRollCommand.h>
#import <RobotCommandKit/RKSetPIDCommand.h>
#import <RobotCommandKit/RKGetSkuCommand.h>
#import <RobotCommandKit/FWLevel1DiagnosticCommand.h>
#import <RobotCommandKit/FWLevel1DiagnosticChunkedCommand.h>
#import <RobotCommandKit/RKForceChargeCommand.h>

#pragma mark - LEDS
#import <RobotCommandKit/RKGetUserRGBLEDColorCommand.h>
#import <RobotCommandKit/RKRGBLEDOutputCommand.h>
#import <RobotCommandKit/RKBackLEDOutputCommand.h>

#pragma mark - Utils
#import <RobotCommandKit/RKMath.h>
#import <RobotCommandKit/RKMajorMinorVersion.h>

#pragma mark - Responses
#import <RobotCommandKit/RKResponseFactory.h>
#import <RobotCommandKit/RKGoToSleepResponse.h>
#import <RobotCommandKit/RKVersioningResponse.h>
#import <RobotCommandKit/RKPingResponse.h>
#import <RobotCommandKit/RKJumpToBootloaderResponse.h>
#import <RobotCommandKit/RKSetBluetoothNameResponse.h>
#import <RobotCommandKit/RKGetBluetoothInfoResponse.h>
#import <RobotCommandKit/RKGetPowerStateResponse.h>
#import <RobotCommandKit/RKSetPowerNotificationResponse.h>
#import <RobotCommandKit/RKSetInactivityTimeoutResponse.h>
#import <RobotCommandKit/RKSetAutoReconnectResponse.h>
#import <RobotCommandKit/RKGetAutoReconnectResponse.h>
#import <RobotCommandKit/RKJumpToMainAppResponse.h>
#import <RobotCommandKit/RKGetUserRGBLEDColorResponse.h>
#import <RobotCommandKit/RKRGBLEDOutputResponse.h>
#import <RobotCommandKit/RKBackLEDOutputResponse.h>
#import <RobotCommandKit/RKSetHeadingResponse.h>
#import <RobotCommandKit/RKRotationRateResponse.h>
#import <RobotCommandKit/RKSetDataStreamingResponse.h>
#import <RobotCommandKit/RKStabilizationResponse.h>
#import <RobotCommandKit/RKRawMotorValuesResponse.h>
#import <RobotCommandKit/RKConfigureCollisionDetectionResponse.h>
#import <RobotCommandKit/RKSetUserHackModeResponse.h>
#import <RobotCommandKit/RKGetDeviceModeResponse.h>
#import <RobotCommandKit/RKConfigureLocatorResponse.h>
#import <RobotCommandKit/RKSelfLevelResponse.h>
#import <RobotCommandKit/RKSetMotionTimeoutResponse.h>
#import <RobotCommandKit/RKSetOptionFlagsResponse.h>
#import <RobotCommandKit/RKGetOptionFlagsResponse.h>
#import <RobotCommandKit/RKSetNonPersistentOptionFlagsResponse.h>
#import <RobotCommandKit/RKGetNonPersistentOptionFlagsResponse.h>
#import <RobotCommandKit/RKSetFactoryDeviceModeResponse.h>
#import <RobotCommandKit/RKGetChassisIdResponse.h>
#import <RobotCommandKit/RKGetSkuResponse.h>
#import <RobotCommandKit/FWLevel1DiagnosticResponse.h>
#import <RobotCommandKit/FWLevel1DiagnosticChunkedResponse.h>
#import <RobotCommandKit/RKGetChargerStateResponse.h>

#pragma mark - Async Data
#import <RobotCommandKit/RKCollisionDetectedAsyncData.h>
#import <RobotCommandKit/RKSelfLevelCompleteAsyncData.h>
#import <RobotCommandKit/RKDeviceSensorsAsyncData.h>
#import <RobotCommandKit/RKDeviceSensorsData.h>
#import <RobotCommandKit/RKAccelerometerData.h>
#import <RobotCommandKit/RKMagnetometerData.h>
#import <RobotCommandKit/RKAttitudeData.h>
#import <RobotCommandKit/RKGyroData.h>
#import <RobotCommandKit/RKBackEMFData.h>
#import <RobotCommandKit/RKLocatorData.h>
#import <RobotCommandKit/RKQuaternionData.h>
#import <RobotCommandKit/RKPowerNotificationAsyncData.h>
#import <RobotCommandKit/FWLevel1DiagnosticAsyncData.h>
#import <RobotCommandKit/FWLevel1DiagnosticChunkedAsyncData.h>

#pragma mark - Async - new naming convention
#import <RobotCommandKit/RKSleepWillOccurMessage.h>
#import <RobotCommandKit/RKSleepDidOccurMessage.h>

// odometer
#import <RobotCommandKit/RKReadOdometerCommand.h>
#import <RobotCommandKit/RKReadOdometerResponse.h>

#import <RobotCommandKit/RKTypes.h>

#import <RobotCommandKit/RKTemperatureCommand.h>
#import <RobotCommandKit/RKTemperatureResponse.h>

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

