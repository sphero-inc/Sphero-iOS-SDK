//
//  RKDeviceMessageCoding.h
//  RobotKit
//
//  Created by Brian Smith on 11/5/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RKDeviceMessageEncoder;
@class RKDeviceMessageDecoder;


@protocol RKDeviceMessageCoding <NSObject>

- (id) initWithDeviceMessageDecoder:(RKDeviceMessageDecoder *) decoder;
- (void) encodeWithDeviceMessageEncoder:(RKDeviceMessageEncoder *) encoder;

@end
