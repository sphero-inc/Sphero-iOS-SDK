#import "RKAsyncMessage.h"

typedef NS_ENUM(uint8_t, RKSelfLevelCompleteResultCode) {
    RKSelfLevelCompleteResultCodeUnknown = 0x00,
    RKSelfLevelCompleteResultCodeTimeOut = 0x01,
    RKSelfLevelCompleteResultCodeSensorsError = 0x02,
    RKSelfLevelCompleteResultCodeSelfLevelDisable = 0x03,
    RKSelfLevelCompleteResultCodeAborted = 0x04,
    RKSelfLevelCompleteResultCodeChargerNotFound = 0x05,
    RKSelfLevelCompleteResultCodeSuccess = 0x06
};

@interface RKSelfLevelCompleteAsyncData : RKAsyncMessage

@property (nonatomic, assign, readonly) RKSelfLevelCompleteResultCode resultCode;

@end
