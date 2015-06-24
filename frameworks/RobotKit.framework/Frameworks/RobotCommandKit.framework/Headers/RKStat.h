//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(int, RKStatKey) {
    RKStatKeyDistanceDriven = 0,
    RKStatKeyRGBChange = 1,
    RKStatKeyMacroRun = 2,
    RKStatKeyCollision = 3,
    RKStatKeyBluetoothConnectionEvent = 4,
    RKStatKeyConnectTime = 5,
    RKStatKeyOdometer = 6,
    RKStatKeyRobotProfile = 7,
};

@interface RKStat : NSObject

@property (nonatomic, readonly) RKStatKey statKey;
@property (strong, nonatomic, readonly) NSString *stringStatKey;
@property (strong, nonatomic, readonly) NSString *associatedMac;

+ (instancetype)statWithKey:(RKStatKey)key mac:(NSString *)mac;

- (void)addDataToStatWithKey:(NSString *)key value:(NSString *)value;

- (NSDictionary *)getDataDictionary;

- (NSData *)serialize;
+ (instancetype)deserialize:(NSData *)statData;

+ (NSString *)filterMac:(NSString *)mac;


@end
