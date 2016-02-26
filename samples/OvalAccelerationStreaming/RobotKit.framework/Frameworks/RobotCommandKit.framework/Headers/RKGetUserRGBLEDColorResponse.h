//
//  RKGetUserRGBLEDColorResponse.h
//  RobotKit
//
//  Created by Brian Smith on 5/17/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKDeviceResponse.h"

/*!
 * Response that contains the user's prefered RGB color. These values can be set using the RKRGBLEDOutputCommand
 * by setting the user default color to true. 
 *
 * @sa RKGetUserRGBLEDColorCommand
 * @sa RKRGBLEDOutputCommand
 */
@interface RKGetUserRGBLEDColorResponse : RKDeviceResponse {
   float redIntensity;
   float greenIntensity;
   float blueIntensty;
}

/*! Returns a value from 0.0 to 1.0 indicating the red LED intensity. */
@property ( nonatomic, readonly ) float redIntensity;
/*! Returns a value from 0.0 to 1.0 indicating the green LED intensity. */
@property ( nonatomic, readonly ) float greenIntensity;
/*! Returns a value from 0.0 to 1.0 indicating the blue LED intensity. */
@property ( nonatomic, readonly ) float blueIntensity;

@end
