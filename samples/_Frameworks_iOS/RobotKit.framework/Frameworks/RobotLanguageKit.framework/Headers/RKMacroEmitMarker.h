//
//  Copyright (c) 2011-2014 Orbotix Inc. All rights reserved.
//

/*! @file */
#import <RobotCommandKit/RKAsyncMessage.h>

/*!
 * Class to encapsulate asyncronous messages sent from a Sphero. 
 */
@interface RKMacroEmitMarker : RKAsyncMessage {
@private
   unsigned char markerId;
   unsigned char macroId;
   unsigned short macroLineNumber;
}

/*! The marker identifier */
@property ( nonatomic, readonly ) unsigned char markerId;
/*! The macro identifier which emited the marker */
@property ( nonatomic, readonly ) unsigned char macroId;
/*! The line number in the macro where the emit marker command was invoked. */
@property ( nonatomic, readonly ) unsigned short macroLineNumber;

@end
