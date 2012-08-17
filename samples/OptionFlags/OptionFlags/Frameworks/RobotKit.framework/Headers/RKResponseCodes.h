/*
 *  RKResponseCodes.h
 *  RobotKit
 *
 *  Created by Brian Smith on 5/31/11.
 *  Copyright 2011 Orbotix Inc. All rights reserved.
 *
 */

enum {
	RKResponseCodeOK				= 0x00,
	RKResponseCodeErrorGeneral		= 0x01,
	RKResponseCodeErrorChecksum		= 0x02,
	RKResponseCodeErrorFragment		= 0x03,
	RKResponseCodeErrorBadCommand	= 0x04,
	RKResponseCodeErrorUnsupported	= 0x05,
	RKResponseCodeErrorBadMessage	= 0x06,
	RKResponseCodeErrorParameter	= 0x07,
	RKResponseCodeErrorExecute		= 0x08,
};

// framework defined error codes
enum {
    RKResponseCodeErrorTimeout      = -2
};