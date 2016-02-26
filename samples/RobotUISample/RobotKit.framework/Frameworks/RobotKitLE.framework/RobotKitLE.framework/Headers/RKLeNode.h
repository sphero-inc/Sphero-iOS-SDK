//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <CoreBluetooth/CoreBluetooth.h>

/*! abstracted radio link state
 @note this is the state that the robot is trying to enter
 */
typedef NS_ENUM (uint8_t, RKLEConnectionState) {
    /*! The communication link with a robot is not valid. */
    RKLEConnectionState_Offline,
    /*! Services and Characteristics are being discovered and configured */
    RKLEConnectionState_Connecting,
    /*! The robot is responding to communications and ready for commands to be sent. */
    RKLEConnectionState_Connected
};

@protocol RKLeNode;
@class RKRadioDescriptor;


@protocol RKLeInternalConnectDelegate <NSObject>

-(void)nodeDidConnect:(id<RKLeNode>) node;
-(void)nodeDidWake:(id<RKLeNode>) node;

@end



/*! data to enable a connect strategy to pick the best device to connect to */
@protocol RKLeNode <NSObject>

@property (nonatomic, readonly) NSNumber *RSSI;
@property (strong, nonatomic) NSDate* lastSeen;

/*! Current robot TX Power - advertised & updated when WriteRobotTxPower is requested
 @note range: -18 to +8 */
@property (nonatomic, readonly) NSNumber *advertisePower;
@property (strong, nonatomic, readonly) CBPeripheral* peripheral;
@property (strong, nonatomic, readonly) CBCentralManager* centralManager;
@property (nonatomic, weak, readonly) id<RKLeInternalConnectDelegate> connectDelegate;

/*! state Link is attempting to obtain */
@property (nonatomic, readonly) RKLEConnectionState connectionState;

-(id) initWithPeripheral:(CBPeripheral*) p andCentral:(CBCentralManager*) mgr;

-(NSString*) name;
-(NSNumber*) signalQuality;
-(BOOL)isConnecting;
-(BOOL)isConnected;

@optional
-(void) startServiceDiscoveryWith:(RKRadioDescriptor*) radioDescriptor;

@end