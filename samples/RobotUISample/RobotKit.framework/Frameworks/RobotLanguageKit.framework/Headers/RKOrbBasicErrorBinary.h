//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RKAsyncMessage.h>

/*!
 * Class to encapsulate asyncronous messages sent from a Sphero.
 */
@interface RKOrbBasicErrorBinary : RKAsyncMessage

/*! The binary error data returned from the Sphero */
@property ( nonatomic, readonly ) NSData *errorData;

@end
