#import "RKDeviceResponse.h"

@interface RKGetUserRGBLEDColorResponse : RKDeviceResponse

@property (nonatomic, assign, readonly) float redIntensity;
@property (nonatomic, assign, readonly) float greenIntensity;
@property (nonatomic, assign, readonly) float blueIntensity;

@end
