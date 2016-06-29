#import <RobotCommandKit/RobotCommandKit.h>

typedef NS_ENUM(uint8_t, RKMacroIdType) {
	RKDeviceMacroIdFigureEight = 1,
	RKDeviceMacroIdSquare = 2
};

@interface RKRunMacroCommand : RKDeviceCommand

@property (nonatomic, assign, readonly) RKMacroIdType macroId;

- (instancetype)initWithId:(RKMacroIdType)identifier;

@end
