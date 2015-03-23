//
//  Copyright (c) 2014 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <RobotCommandKit/RKLinkDelegate.h>
#import "RKLESession.h"
#import "RKLeConnectStrategy.h"
#import "RKLeBaseLink.h"

extern NSString * const kRobotRadioAckNotificationIdKey;
extern NSString * const kRobotRadioAckNotificationLastPacketKey;


// todo - move to robot & share with original SDK
/*! main processor state */
typedef NS_ENUM (uint8_t, RKLEMainProcessorState){
    RKLEMainProcessorState_Offline = 0,
    
    RKLEMainProcessorState_MainProcessorPowerOnRequested = 10,
    
    // Bluetooth Classic states start here.  > 10
    RKLEMainProcessorState_MainProcessorPowerOn = 11,
    
    RKLEMainProcessorState_JumpToBootloaderRequested = 20,
    RKLEMainProcessorState_JumpToBootloaderFailed = 21, /*! Failed to go to bootloader, and is still in the app. */
    RKLEMainProcessorState_InBootloader = 22,
    
    
    RKLEMainProcessorState_JumpToMainAppRequested = 90,
    RKLEMainProcessorState_MainAppCorrupt = 91, /*! The robot reported a main app corrupt error, and is stuck in the bootloader. */
    
    RKLEMainProcessorState_InMainApp = 100, // in main app (9)
    RKLEMainProcessorState_OfflineRequested = 101
};

typedef NS_ENUM (uint8_t, RKLEWakeType){
	RKLeWakeType_Normal = 0x01,
	RKLeWakeType_Silent = 0x02
};

/*!
 Manages the bluetooth low-energy (4.0) RF Link
 @see RKClassicLink for classic bluetooth
 @author wes felteau
 */
@interface RKLeRobotLink : RKLeBaseLink

@property (weak, nonatomic, readonly) id<RKLinkDelegate, RKSessionDelegate> linkDelegate; // typically the robot

@property (readwrite) float rssiUpdateDelay; // should be in monitor

/*! current main processor state */
@property (readonly) RKLEMainProcessorState mpState;

/* used to throttle roll, colorchange and other commands until an ACK is received from the bt processor */
@property (readonly) BOOL driveLock;
@property (readonly) BOOL rgbLock;

/*! 0 = ACK, 1 = broadcast */
@property (readwrite) NSInteger driveMode; // ack or broadcast modes.
@property (readonly) NSTimeInterval driveAckLatency; // x/2
@property (readonly) NSMutableArray* latencyList;


-(id) initWithPeripheral:(CBPeripheral*) p andConnectionDelegate:(id<RKLinkDelegate>) delegate;

-(void) sendCommand:(RKDeviceCommand*) cmd;
-(void) streamCommand:(RKDeviceCommand*) cmd;


/*! request Wake */
-(void) requestMainProcessorPowerOn;
-(void) requestMainProcessorPowerOn:(RKLEWakeType) wakeType;

/*! once awake, requestMainApp */
-(void) requestMainApp;

/*! hard shut down robot - requires USB power to restart robot */
-(void) deepSleep;

/* write new Tx Power to robot */
-(void) writeRemoteTxPower:(NSNumber*)txPower;
-(void) sendRaw:(NSData*) data;

-(void) setDeveloperMode:(BOOL) yn;

-(CBPeripheralState) radioState;

#pragma mark - Native BLE Device Info

/*! gee - wonder what this could be */
@property (strong, nonatomic, readonly) RKMajorMinorVersion* rfVersion;

/*! BLE actual MAC Address - iOS obfuscates the address so we at Orbotix have exposed it as a serial number. */
@property (strong, nonatomic, readonly) NSString* serialNumber;

@end