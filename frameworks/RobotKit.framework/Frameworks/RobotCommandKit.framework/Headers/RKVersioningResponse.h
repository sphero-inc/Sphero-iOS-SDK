//
//  Copyright 2014 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import "RKDeviceResponse.h"
#import "RKMajorMinorVersion.h"


typedef NS_ENUM( uint8_t, RKRobotModel ){
	SpheroS1  = 0,
	OllieBadFirmware = 1,
	SpheroS2  = 2,
	SpheroS3  = 3,
	Unknown4  = 4,
	Ollie01   = 10,
	BB8_01    = 30,
	WeBall    = 40
};



/*!
 * @brief Class to encapsulate the version numbers returned from a versioning command.
 *
 * Provides all of the versioning data returned from a versioning command.
 * 
 * @sa RKVersioningCommand
 */
@interface RKVersioningResponse : RKDeviceResponse

/*! A version number for the version data returned. Currently set to 1.*/
@property ( strong, nonatomic, readonly ) NSString *recordVersion;
/*! The model number of the robot. */
@property ( nonatomic, readonly ) RKRobotModel modelNumber;
/*! A version number for the hardware. This a single digit number. */
@property ( strong, nonatomic, readonly ) NSString *hardwareVersion;
/*! The version number for the main application which makes the robot do what it does. 
 * The version string is in major.minor format, ex. 0.96.
 */
@property ( strong, nonatomic, readonly ) RKMajorMinorVersion *mainAppVersion;
/*! The version number of the bootloader in major.minor format, ex. 1.7 */
@property ( strong, nonatomic, readonly ) RKMajorMinorVersion *bootloaderVersion;
/*! The version number for the OrbBasic interpreter in major.minor format, ex. 1.0 */
@property ( strong, nonatomic, readonly ) NSString *orbBasicVersion;
/*! The version number of the macro processor in major.minor format, 1.0 */
@property ( strong, nonatomic, readonly ) NSString *overlayManagerVersion;

@end
