//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(uint8_t, RKStatKey) {
    RKStatKeyDistanceDriven,
    RKStatKeyRGBChange,
    RKStatKeyMacroRun,
    RKStatKeyCollision,
    RKStatKeyBluetoothConnectionEvent,
    RKStatKeyConnectTime,
    RKStatKeyOdometer,
    RKStatKeyRobotProfile,
};

typedef NS_ENUM(uint8_t, RKStatDataKey) {
    RKStatDataKeyId,
    RKStatDataKeyTime,
    RKStatDataKeyValue,
    RKStatDataKeyCm,
    RKStatDataKeyHex,
    RKStatDataKeyName,
    RKStatDataKeySerialNumber,
    RKStatDataKeyModel,
    RKStatDataKeyMainApp,
    RKStatDataKeyBootloader,
    RKStatDataKeyRadioFirmware,
    RKStatDataKeySku,
    RKStatDataKeyChassisId,
    RKStatDataKeyFactoryConfigBlockCRC,
};

@interface RKStat : NSObject

@property (nonatomic, readonly) RKStatKey statKey;
@property (strong, nonatomic, readonly) NSString *stringStatKey;
@property (strong, nonatomic, readonly) NSString *associatedMac;

+ (instancetype)statWithKey:(RKStatKey)key mac:(NSString *)mac;

- (void)addDataToStatWithKey:(RKStatDataKey)key value:(NSString *)value;
- (void)addDataToStatWithKey:(RKStatDataKey)key uintValue:(uint32_t)uintValue;

- (NSDictionary *)getDataDictionary;

- (NSData *)serialize;
+ (instancetype)deserialize:(NSData *)statData;

+ (NSString *)filterMac:(NSString *)mac;


@end
