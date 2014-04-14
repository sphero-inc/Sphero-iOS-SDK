//
//  RKPollPacketTimesResponse.h
//  RobotKit
//
//  Created by Brian Smith on 2/24/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import "RKDeviceResponse.h"

/*! @brief Response class for polling for transmission time stamps.
 
    This response to RKPollPacketTimesCommand helps the Client application profile the transmission and processing latencies in Sphero so that a relative synchronization of timebases can be performed. This technique is based upon the scheme in the Network Time Protocol (RFC 5905) and allows the Client to reconcile time stamped messages from Sphero to its own time stamped events. In the following discussion, each time interval is from some reference within the device.
 
    The scheme is as follows: the Client sends the command with the Client transmit time (T1). Upon receipt of the packet, the command processor in Sphero copies that time (T2) into the response packet. Just before the transmit engine streams it into the Bluetooth module, the Sphero transmit time (T3) value is added to the response packet. The framework sets in the response object the time (T4) at which the response is received. The relevant time segments can be computed from the four time stamps T1-T4:
    <ul>
    <li> The value offset represents the maximum-likelihood time offset of the Client clock to Sphero's system clock.
    offset = 1/2 * [(T2 - T1) + (T3 - T4)]</li>
    <li>The value delay represents the round-trip delay between the Client and Sphero:
    delay = (T4 - T1) - (T3 - T2)</li>
    </ul>
    @sa RKPollPacketTimesCommand
    @sa RKDeviceMessenger
 */
@interface RKPollPacketTimesResponse : RKDeviceResponse {
@private
   NSTimeInterval commandTransmitTime;
   NSTimeInterval robotReceiveTime;
   NSTimeInterval robotTransmitTime;
}

/*! @return The controller device's transmit time stamp in seconds in it's time reference. */
@property ( nonatomic, readonly ) NSTimeInterval commandTransmitTime;
/*! @return The robot's receive time stamp in seconds in it's time reference. */
@property ( nonatomic, readonly ) NSTimeInterval robotReceiveTime;
/*! @return The robot's transmit time stamp in seconds in it's time reference. */
@property ( nonatomic, readonly ) NSTimeInterval robotTransmitTime;

/*!
 * @return A value in seconds for the offset between the controlling device's clock and the robot's clock.
 */
- (NSTimeInterval) timeOffset;
/*!
 * @return A value in seconds for the delay from sending a command and receiving it's response. 
 */
- (NSTimeInterval) timeDelay;

@end
