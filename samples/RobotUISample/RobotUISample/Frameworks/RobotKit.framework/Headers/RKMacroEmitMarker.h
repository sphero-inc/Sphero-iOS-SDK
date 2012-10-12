//
//  RKMacroEmitMarker.h
//  RobotKit
//
//  Created by Brian Smith on 10/14/11.
//  Copyright (c) 2011 Orbotix Inc. All rights reserved.
//

/*! @file */
#import "RKDeviceAsyncData.h"

/*!
 * Class to encapsulate asyncronous messages sent from a Sphero. To receive this object
 * register as an asynchronous data observer with RKDeviceMessenger.
 */
@interface RKMacroEmitMarker : RKDeviceAsyncData {
    @private 
    unsigned char   markerId;
    unsigned char   macroId;
    unsigned short  macroLineNumber;
}

/*! The marker identifier */
@property (nonatomic, readonly) unsigned char markerId;
/*! The macro identifier which emited the marker */
@property (nonatomic, readonly) unsigned char macroId;
/*! The line number in the macro where the emit marker command was invoked. */
@property (nonatomic, readonly) unsigned short macroLineNumber;

@end
