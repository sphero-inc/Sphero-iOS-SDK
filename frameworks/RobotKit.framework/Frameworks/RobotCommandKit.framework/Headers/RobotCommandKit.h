//
//  Copyright (c) 2014-2015 Orbotix Inc. All rights reserved.
//

#import "RKLinkDelegate.h"
#import "RKSession.h"
#import "RKRobotBase.h"
#import "RKDiscoveryAgent.h"
#import "RKAppUtils.h"

#pragma mark - all robots
#import "RKRobotNotification.h"
#import "NSData+Extensions.h"

// Drive algorithms
#import "RKDriveAlgorithm.h"
#import "RKJoyStickDriveAlgorithm.h"

// Common
#import "RKDeviceMessage.h"
#import "RKDeviceCommand.h"

#import "RKDeviceAsyncData.h" // deprecated - replaced with RKAsyncMessage
#import "RKAsyncMessage.h"
#import "RKDeviceResponse.h"
#import "RKImmutableCommand.h"
#import "RKByteCommand.h"
#import "RKResponseCodes.h"


//// Core
#import "RKGetAutoReconnectCommand.h"
#import "RKGetBluetoothInfoCommand.h"
#import "RKGetPowerStateCommand.h"
#import "RKPingCommand.h"
#import "RKPollPacketTimesCommand.h"
#import "RKSetAutoReconnectCommand.h"
#import "RKSetBluetoothNameCommand.h"
#import "RKSetInactivityTimeoutCommand.h"
#import "RKSetPowerNotificationCommand.h"
#import "RKVersioningCommand.h"
#import "RKJumpToBootloaderCommand.h"
#import "RKGoToSleepCommand.h"
#import "RKGetChargerStateCommand.h"

//// Bootloader
#import "RKJumpToMainAppCommand.h"


#pragma mark - Commands
#import "RKRollCommand.h"
#import "RKGetChassisIdCommand.h"
#import "RKCalibrateCommand.h"
#import "RKStabilizationCommand.h"
#import "RKSetHeadingCommand.h"
#import "RKRotationRateCommand.h"
#import "RKSetDataStreamingCommand.h"
#import "RKRawMotorValuesCommand.h"
#import "RKConfigureCollisionDetectionCommand.h"
#import "RKSetUserHackModeCommand.h"
#import "RKGetDeviceModeCommand.h"
#import "RKConfigureLocatorCommand.h"
#import "RKSelfLevelCommand.h"
#import "RKSetMotionTimeoutCommand.h"
#import "RKSetOptionFlagsCommand.h"
#import "RKGetOptionFlagsCommand.h"
#import "RKSetNonPersistentOptionFlagsCommand.h"
#import "RKGetNonPersistentOptionFlagsCommand.h"
#import "RKSetFactoryDeviceModeCommand.h"
#import "RKRollCommand.h"
#import "RKSetPIDCommand.h"
#import "RKGetSkuCommand.h"
#import "FWLevel1DiagnosticCommand.h"
#import "RKForceChargeCommand.h"

#pragma mark - LEDS
#import "RKGetUserRGBLEDColorCommand.h"
#import "RKRGBLEDOutputCommand.h"
#import "RKBackLEDOutputCommand.h"

#pragma mark - Utils
#import "RKMath.h"
#import "RKMajorMinorVersion.h"


#pragma mark - Responses
#import "RKResponseFactory.h"
#import "RKGoToSleepResponse.h"
#import "RKVersioningResponse.h"
#import "RKPingResponse.h"
#import "RKJumpToBootloaderResponse.h"
#import "RKSetBluetoothNameResponse.h"
#import "RKGetBluetoothInfoResponse.h"
#import "RKGetPowerStateResponse.h"
#import "RKPollPacketTimesResponse.h"
#import "RKSetPowerNotificationResponse.h"
#import "RKSetInactivityTimeoutResponse.h"
#import "RKSetAutoReconnectResponse.h"
#import "RKGetAutoReconnectResponse.h"
#import "RKJumpToMainAppResponse.h"
#import "RKGetUserRGBLEDColorResponse.h"
#import "RKRGBLEDOutputResponse.h"
#import "RKBackLEDOutputResponse.h"
#import "RKByteResponse.h"
#import "RKSetHeadingResponse.h"
#import "RKCalibrateResponse.h"
#import "RKRollResponse.h"
#import "RKRotationRateResponse.h"
#import "RKSetDataStreamingResponse.h"
#import "RKStabilizationResponse.h"
#import "RKRawMotorValuesResponse.h"
#import "RKConfigureCollisionDetectionResponse.h"
#import "RKSetUserHackModeResponse.h"
#import "RKGetDeviceModeResponse.h"
#import "RKConfigureLocatorResponse.h"
#import "RKSelfLevelResponse.h"
#import "RKSetMotionTimeoutResponse.h"
#import "RKSetOptionFlagsResponse.h"
#import "RKGetOptionFlagsResponse.h"
#import "RKSetNonPersistentOptionFlagsResponse.h"
#import "RKGetNonPersistentOptionFlagsResponse.h"
#import "RKSetFactoryDeviceModeResponse.h"
#import "RKGetChassisIdResponse.h"
#import "RKGetSkuResponse.h"
#import "FWLevel1DiagnosticResponse.h"
#import "RKGetChargerStateResponse.h"

#pragma mark - Async Data
#import "RKCollisionDetectedAsyncData.h"
#import "RKSelfLevelCompleteAsyncData.h"
#import "RKDeviceSensorsAsyncData.h"
#import "RKDeviceSensorsData.h"
#import "RKAccelerometerData.h"
#import "RKMagnetometerData.h"
#import "RKAttitudeData.h"
#import "RKGyroData.h"
#import "RKBackEMFData.h"
#import "RKLocatorData.h"
#import "RKQuaternionData.h"
#import "RKPowerNotificationAsyncData.h"
#import "FWLevel1DiagnosticAsyncData.h"

#pragma mark - Async - new naming convention
#import "RKSleepWillOccurMessage.h"
#import "RKSleepDidOccurMessage.h"

// odometer
#import "RKReadOdometerCommand.h"
#import "RKReadOdometerResponse.h"


#import "RKResponseFactory_PrivateAdditions.h"
#import "RKAsyncFactory_PrivateAdditions.h"

#import "RKTypes.h"


#import "RKTemperatureCommand.h"
#import "RKTemperatureResponse.h"

#define SYSTEM_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)

