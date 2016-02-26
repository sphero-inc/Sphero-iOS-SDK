//
//  Copyright (c) 2015 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RobotCommandKit.h>

extern const ushort MINIMUM_BLOCK_ID;
extern const ushort MAXIMUM_BLOCK_ID;

@interface RKWritePersistentPageCommand : RKDeviceCommand

+ (instancetype)new NS_UNAVAILABLE;
+ (instancetype)commandWithPage:(NSData *)page andBlockId:(ushort)blockId;

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithPage:(NSData *)page andBlockId:(ushort)blockId;

@end
