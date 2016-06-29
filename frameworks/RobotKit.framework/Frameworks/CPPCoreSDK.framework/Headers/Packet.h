#pragma once
#include "APIV2.h"
#include <vector>
#include "APIV2Constants.h"

namespace apiv2 
{
	class APIV2PROCESSOR_API Packet
	{
	public:
		Packet(std::vector<uint8_t> rawPacket);
		Packet(uint8_t flags, uint8_t id0, uint8_t id1, uint8_t sequenceNumber, std::vector<uint8_t> data);
		Packet(uint8_t flags, uint8_t id0, uint8_t id1, std::vector<uint8_t> data);
		uint8_t getFlags();
		uint8_t getId0();
		uint8_t getId1();
		uint8_t getSequenceNumber();
		uint8_t getChecksum();
		const std::vector<uint8_t> getData();
		const std::vector<uint8_t> getRawPacket();
	private:
		std::vector<uint8_t> _rawPacket;
	};
}