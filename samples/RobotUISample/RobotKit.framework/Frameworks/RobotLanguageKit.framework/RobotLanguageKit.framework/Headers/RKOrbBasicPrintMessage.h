//
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <RobotCommandKit/RKAsyncMessage.h>

/*!
 * Class to encapsulate asyncronous messages sent from a Sphero. 
 */
@interface RKOrbBasicPrintMessage : RKAsyncMessage {
@private
   NSString *message;
}

/*! The message that was returned from orbBasic for printing on the screen. */
@property ( nonatomic, readonly ) NSString *message;

@end
