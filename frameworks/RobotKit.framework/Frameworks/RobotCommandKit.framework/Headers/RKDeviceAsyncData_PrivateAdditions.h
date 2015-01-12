//
//  Copyright 2011-2014 Orbotix Inc. All rights reserved.
//

#import "RKDeviceAsyncData.h"

/*! @ignore */
@interface RKDeviceAsyncData (PrivateAdditions)

/**
 * Accessor to the identifier of the async data the class encapsulates.
 * @return The data identifier.
 */
+ (uint8_t) dataIdentifier;

/**
 *  Call this initializer from subclasses, which checks that the code matches the 
 *  data identifier of the packet data.
 *  @param code The identifier of the data being sent.
 *  @return The object instance. This will be nil if the code doesn't match the 
 *  data identifier.
 */
//- (id) initWithCode:(uint8_t) code;

/**
 * The base class uses this to find subclasses and it instanciates them. Subclass
 * should over ride this in order to unpack the data, and the override method should
 * call initWithCode: which checks the code with data identifier it supports.
 * @param code The code value that identifies the data received.
 * @param data The data received in the async data packet.
 * @return The object instance or nil if the data can not be handle by the class.
 */
//- (id) initWithCode:(uint8_t) code data:(NSData *) data;


- (id) initWithAsyncPacket:(NSData*) packet;


@end