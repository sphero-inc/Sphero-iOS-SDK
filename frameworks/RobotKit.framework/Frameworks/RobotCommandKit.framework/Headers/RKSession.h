#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKAsyncMessage.h"
#import "RKDeviceCommand.h"

@protocol RKSessionDelegate <NSObject>

- (void)handleResponse:(RKDeviceResponse *)response;
- (void)handleStringResponse:(NSString *)stringResponse;
- (void)handleAsyncData:(RKAsyncMessage *)asyncData;

@end

@protocol RKSession <NSObject>

@property (nonatomic, weak) id<RKSessionDelegate> delegate;

- (instancetype)initWithDelegate:(id<RKSessionDelegate>)delegate;
- (void)processRawData:(NSData *)data;
- (NSData *)generatePacketFromCommand:(RKDeviceCommand *)command;

@end