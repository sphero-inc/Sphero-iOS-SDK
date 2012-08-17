//
//  RKGetUserRGBLEDColorCommand.h
//  RobotKit
//
//  Created by Brian Smith on 5/17/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

#import "RKDeviceCommand.h"

/*!
 * Use this command to get the users default color which is returned in the response. It is initially set to Sphero blue until set
 * using RKRGBLEDOutputCommand and setting the user default flag to true. This color is displayed when Sphero is first connected 
 * and no color is commanded. Also, it can be used in application to set as the user prefered color, until an application specific 
 * color is set.
 *
 * @sa RKGetUserRGBLEDColorCommand
 * @sa RKRGBLEDOutputCommand
 */
@interface RKGetUserRGBLEDColorCommand : RKDeviceCommand

@end
