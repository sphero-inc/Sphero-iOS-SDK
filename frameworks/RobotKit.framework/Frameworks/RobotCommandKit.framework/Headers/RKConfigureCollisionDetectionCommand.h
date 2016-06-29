#import "RKDeviceCommand.h"

typedef NS_ENUM(uint8_t,  RKCollisionDetectionMethod ){
	RKCollisionDetectionMethodDetectionOff = 0,
	RKCollisionDetectionMethod1 = 1,
	RKCollisionDetectionMethod2 = 2,
	RKCollisionDetectionMethod3 = 3
};

@interface RKConfigureCollisionDetectionCommand : RKDeviceCommand

- (nullable instancetype)initForMethod:(RKCollisionDetectionMethod)method
                            xThreshold:(uint8_t)xThreshold
                       xSpeedThreshold:(uint8_t)xSpeedThreshold
                            yThreshold:(uint8_t)yThreshold
                       ySpeedThreshold:(uint8_t)ySpeedThreshold
                      postTimeDeadZone:(NSTimeInterval)deadZone;

@end
