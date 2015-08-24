//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

@interface RKRadioDescriptor : NSObject

-(id) init; // for subclasses.

-(id) initWithAdvertised:(NSArray*) adUUIDS andRequiredUUIDS:(NSArray*) reqUUIDS;

+(id) descriptorWithAdvertisedUUIDS:(NSArray*) adUUIDS andRequiredUUIDS:(NSArray*) reqUUIDS;

/*! Services advertised by the remote device*/
@property (strong , readonly) NSArray* advertisedUUIDS;

/*! Required service UUIDS for the device to function */
@property (strong, readonly) NSArray* requiredUUIDS;

/*! */
@property (strong) NSArray* namePrefixes;

// SpheroCo Radio service and characteristics
@property (strong) CBUUID* uuidRadioService;
@property (strong) CBUUID* uuidTxPowerCharacteristic;
@property (strong) CBUUID* uuidDeepSleepCharacteristic;
@property (strong) CBUUID* uuidAntiDOSCharacteristic;
@property (strong) CBUUID* uuidAntiDOSTimeoutCharacteristic;
@property (strong) CBUUID* uuidWakeCharacteristic;
@property (strong) CBUUID* uuidRSSICharacteristic;

- (BOOL)nameMatchesPrefixes:(NSString *)name;

@end
