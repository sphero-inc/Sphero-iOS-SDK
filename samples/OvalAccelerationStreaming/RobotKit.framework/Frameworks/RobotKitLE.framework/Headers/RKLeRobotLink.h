//
//  Copyright (c) 2014 Orbotix. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>
#import <RobotCommandKit/RKLinkDelegate.h>
#import <RobotCommandKit/RKSession.h>
#import <RobotCommandKit/RKMainProcessorState.h>
#import "RKLeConnectStrategy.h"
#import "RKLeBaseLink.h"
#import "RKRadioServiceWrapper.h"


extern NSString * const kRobotRadioAckNotificationIdKey;
extern NSString * const kRobotRadioAckNotificationLastPacketKey;

/*!
 Manages the bluetooth low-energy (4.0) RF Link
 @see RKClassicLink for classic bluetooth
 @author wes felteau
 */
@interface RKLeRobotLink : RKLeBaseLink

@property (weak, nonatomic, readonly) id<RKLinkDelegate, RKSessionDelegate, RKRobotBase> linkDelegate; // typically the robot

@property (readwrite) float rssiUpdateDelay; // should be in monitor

/*! current main processor state */
@property (nonatomic, readonly) RKMainProcessorState mpState;

/*! YES by default - Throttle rgb and drive commands from spammy joysticks and color picker UIs */
 @property () BOOL enableThrottle; // == YES

/*! 0 = ACK, 1 = broadcast */
@property (readwrite) NSInteger driveMode; // ack or broadcast modes.
@property (readonly) NSTimeInterval driveAckLatency; // x/2
@property (readonly) NSMutableArray* latencyList;


-(id) initWithPeripheral:(CBPeripheral*) p andConnectionDelegate:(id<RKLinkDelegate>) delegate;

-(void) sendCommand:(RKDeviceCommand*) cmd;
-(void) streamCommand:(RKDeviceCommand*) cmd;

/*! request Wake */
-(void) requestMainProcessorPowerOn;

/*! once awake, requestMainApp */
-(void) requestMainApp;

/*! hard shut down robot - requires USB power to restart robot */
-(void) deepSleep;

/* write new Tx Power to robot */
-(void) writeRemoteTxPower:(NSNumber*)txPower;
-(void) sendRaw:(NSData*) data;

-(void) setDeveloperMode:(BOOL) yn; // todo use enable instead of set

-(CBPeripheralState) radioState;

#pragma mark - Native BLE Device Info
/*! gee - wonder what this could be */
-(RKMajorMinorVersion*) rfVersion;

/*! BLE actual MAC Address - iOS obfuscates the address so we at Orbotix have exposed it as a serial number. */
-(NSString*) serialNumber;


#pragma mark - new in 2015
/*! Ray */
-(void) requestMainProcessorPowerOn:(RKLEWakeType) wakeType;

/*! Note, fast pings can increase drive latency and when used while main-app is offline, can result in
 a much reduced sleep time.  Only compatible with rfVersion > 1.37+
 */
-(void) enableRemoteRSSIMonitor:(uint16_t) pingIntervalInSeconds;


@end