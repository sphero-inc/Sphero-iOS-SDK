#pragma once
#include <stdint.h>

#define SLIP_ESCAPE_MASK 0x88
#define SLIP_ENCODE(value) ((value) & ~SLIP_ESCAPE_MASK)
#define SLIP_DECODE(value) ((value) | SLIP_ESCAPE_MASK)

namespace apiv2
{
	const uint8_t ESCAPE = 0xAB;
	const uint8_t START_OF_PACKET = 0x8D;
	const uint8_t END_OF_PACKET = 0xD8;
	const uint8_t ESCAPED_ESCAPE = SLIP_ENCODE(ESCAPE);
	const uint8_t ESCAPED_START_OF_PACKET = SLIP_ENCODE(START_OF_PACKET);
	const uint8_t ESCAPED_END_OF_PACKET = SLIP_ENCODE(END_OF_PACKET);
	const int MINIMUM_PACKET_LENGTH = 7;
	
	enum ErrorCode
	{
		badEscapeValue = 0x00,
		badChecksum = 0x01,
		earlyEndOfPacket = 0x02,
		earlyStartOfPacket = 0x03,
        invalidFlags = 0x04
	};

	enum Flags
	{
		none = 0x00,
		isResponse = 0x01,
		requestResponse = 0x02,
		resetInactivityTimeout = 0x04
	};
}