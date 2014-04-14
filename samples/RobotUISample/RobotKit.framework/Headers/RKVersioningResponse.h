//
//  RKVersioningResponse.h
//  RobotKit
//
//  Created by Brian Smith on 5/27/11.
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKDeviceResponse.h>

/*!
 * @enum ModelNumber
 * Model number for Sphero.
 */
typedef enum {
   ModelNumberSphero = 0x02 /*! The model number for Sphero. */
} ModelNumber;


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
/*! The model number of the robot. Current is set to 2 for Sphero. */
@property ( nonatomic, readonly ) ModelNumber modelNumber;
/*! A version number for the hardware. This a single digit number. */
@property ( strong, nonatomic, readonly ) NSString *hardwareVersion;
/*! The version number for the main application which makes the robot do what it does. 
 * The version string is in major.minor format, ex. 0.96.
 */
@property ( nonatomic, readonly ) NSString *mainApplicationVersion;
/*! The version number of the bootloader in major.minor format, ex. 1.7 */
@property ( strong, nonatomic, readonly ) NSString *bootloaderVersion;
/*! The version number for the OrbBasic interpreter in major.minor format, ex. 1.0 */
@property ( strong, nonatomic, readonly ) NSString *orbBasicVersion;
/*! The version number of the macro processor in major.minor format, 1.0 */
@property ( strong, nonatomic, readonly ) NSString *overlayManagerVersion;

@end
