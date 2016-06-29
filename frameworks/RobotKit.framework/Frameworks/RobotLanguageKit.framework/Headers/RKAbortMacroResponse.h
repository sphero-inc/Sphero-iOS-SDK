#import <RobotCommandKit/RobotCommandKit.h>

typedef NS_ENUM(uint8_t, RKAbortMacroCode) {
   RKAbortMacroCodeMacroNotRunning = 0
};

@interface RKAbortMacroResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) RKAbortMacroCode abortCode;

@end
