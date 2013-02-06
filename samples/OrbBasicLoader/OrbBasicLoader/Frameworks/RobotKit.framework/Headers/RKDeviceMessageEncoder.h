//
//  RKDeviceMessageEncoder.h
//  RobotKit
//
//  Created by Brian Smith on 11/5/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol RKDeviceMessageCoding;

@interface RKDeviceMessageEncoder : NSObject {
@private
    NSMutableDictionary *keyedRepresentation;
}

+ (RKDeviceMessageEncoder *)encodeWithRootObject:(id<RKDeviceMessageCoding>)object;

- (id)initWithRootObject:(id<RKDeviceMessageCoding>)object;


- (void)encodeDouble:(double)value forKey:(NSString *)key;
- (void)encodeFloat:(float)value forKey:(NSString *)key;
- (void)encodeInteger:(NSInteger)value forKey:(NSString *)key;
- (void)encodeUnsignedInteger64:(uint64_t)value forKey:(NSString *)key;
- (void)encodeInteger64:(int64_t)value forKey:(NSString *)key;
- (void)encodeBOOL:(BOOL)value forKey:(NSString *)key;
- (void)encodeString:(NSString*)value forKey:(NSString*)key;
- (void)encodeObject:(id)value forKey:(NSString *)key;

- (NSString *)stringRepresentation;

@end
