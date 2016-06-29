//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface RKRadioDescriptor : NSObject

- (id)initWithAdvertised:(NSArray *)adUUIDS andRequiredUUIDS:(NSArray *)reqUUIDS;

+ (id)descriptorWithAdvertisedUUIDS:(NSArray *)adUUIDS andRequiredUUIDS:(NSArray *)reqUUIDS;

/*! Services advertised by the remote device*/
@property (nonatomic, strong , readonly) NSArray* advertisedUUIDS;

/*! Required service UUIDS for the device to function */
@property (nonatomic, strong, readonly) NSArray* requiredUUIDS;

/*! */
@property (nonatomic, strong) NSArray* namePrefixes;

// SpheroCo Radio service and characteristics
@property (nonatomic, strong) CBUUID *uuidRadioService;
@property (nonatomic, strong) CBUUID *uuidTxPowerCharacteristic;
@property (nonatomic, strong) CBUUID *uuidDeepSleepCharacteristic;
@property (nonatomic, strong) CBUUID *uuidAntiDOSCharacteristic;
@property (nonatomic, strong) CBUUID *uuidAntiDOSTimeoutCharacteristic;
@property (nonatomic, strong) CBUUID *uuidSecurityCharacteristic;
@property (nonatomic, strong) CBUUID* uuidWakeCharacteristic;
@property (nonatomic, strong) CBUUID* uuidRSSICharacteristic;

- (BOOL)nameMatchesPrefixes:(NSString *)name;

@end
