//
//  RKDeviceMessageDecoder.h
//  RobotKit
//
//  Created by Brian Smith on 11/5/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RKDeviceMessageDecoder : NSObject {
    @private
    NSDictionary *keyedRepresentation;
    id rootObject;
}

@property (nonatomic, readonly) id rootObject;

+ (RKDeviceMessageDecoder *)decoderWithStringRepersentation:(NSString *)encodedString;


+ (id)rootObjectFromStringRepresentation:(NSString *)encodedString;


- (id)initWithStringRepresentation:(NSString *)encodedString;

- (double)decodeDoubleValueForKey:(NSString *)key;
- (NSInteger)decodeIntegerValueForKey:(NSString *)key;
- (int64_t)decodeInteger64ValueForKey:(NSString *)key;
- (BOOL)decodeBOOLValueForKey:(NSString *)key;
-(id)decodeObjectForKey:(NSString*)key;
-(float)decodeFloatValueForKey:(NSString*)key;

@end
