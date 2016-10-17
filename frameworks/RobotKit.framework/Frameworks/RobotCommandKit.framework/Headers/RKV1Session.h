#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKAsyncMessage.h"
#import "RKDeviceCommand.h"
#import "RKSession.h"

typedef NS_ENUM(uint8_t, RKV1SessionState) {
    RKV1SessionStateWaitingForSop,
    RKV1SessionStateWaitingForFlags,
    RKV1SessionStateWaitingForMSRP,
    RKV1SessionStateWaitingForSequenceNumber,
    RKV1SessionStateWaitingForDlen,
    RKV1SessionStateWaitingForEndOfPacket,
    RKV1SessionStateWaitingForAsyncId,
    RKV1SessionStateWaitingForAsyncDlen1,
    RKV1SessionStateWaitingForAsyncDlen2,
    RKV1SessionStateWaitingForAsyncEndOfPacket
};



@interface RKV1Session : NSObject <RKSession>

@property (nonatomic, weak) id<RKSessionDelegate> delegate;
@property (nonatomic, assign, readonly) RKV1SessionState currentState;


@end
