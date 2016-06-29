#import <RobotCommandKit/RobotCommandKit.h>

@interface RKMacroEmitMarker : RKAsyncMessage

@property (nonatomic, assign, readonly) unsigned char markerId;
@property (nonatomic, assign, readonly) unsigned char macroId;
@property (nonatomic, assign, readonly) unsigned short macroLineNumber;

@end
