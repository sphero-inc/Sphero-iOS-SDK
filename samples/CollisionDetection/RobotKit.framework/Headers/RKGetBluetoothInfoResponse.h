//
//  Copyright 2011 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"

/*!
 * @brief Class that encapsulates the response from a get bluetooth info command.
 *
 * Objects of this class provide the info return from a get bluetooth info command. The 
 * data is invalid if an error was returned.
 *
 * @sa RKGetBluetoothInfoCommand
 */
@interface RKGetBluetoothInfoResponse : RKDeviceResponse {

}

/*! 
 * A name that is stored on the robot as a UTF-8 string. This is not the bluetooth name,
 * so the name can be localized for international character sets.
 */
@property ( nonatomic, readonly, strong ) NSString *name;
/*! The bluetooth address of the robot */
@property ( nonatomic, readonly, strong ) NSString *address;

@end
