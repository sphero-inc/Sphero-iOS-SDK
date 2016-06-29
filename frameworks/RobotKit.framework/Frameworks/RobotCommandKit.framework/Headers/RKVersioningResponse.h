#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKMajorMinorVersion.h"


typedef NS_ENUM(uint8_t, RKRobotModel) {
	SpheroS1  = 0,
	OllieBadFirmware = 1,
	SpheroS2  = 2,
	SpheroS3  = 3,
	Unknown4  = 4,
	Ollie01   = 10,
	BB8_01    = 30,
	WeBall    = 40,
    SprkPlus  = 50,
};

@interface RKVersioningResponse : RKDeviceResponse

@property ( strong, nonatomic, readonly ) NSString *recordVersion;
@property ( nonatomic, readonly ) RKRobotModel modelNumber;
@property ( strong, nonatomic, readonly ) NSString *hardwareVersion;
@property ( strong, nonatomic, readonly ) RKMajorMinorVersion *mainAppVersion;
@property ( strong, nonatomic, readonly ) RKMajorMinorVersion *bootloaderVersion;
@property ( strong, nonatomic, readonly ) NSString *orbBasicVersion;
@property ( strong, nonatomic, readonly ) NSString *overlayManagerVersion;

@end
