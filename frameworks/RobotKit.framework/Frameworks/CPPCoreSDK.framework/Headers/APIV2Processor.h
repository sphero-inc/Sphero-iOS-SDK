#pragma once
#include <vector>
#include <memory>
#include "APIV2.h"
#include "Packet.h"
#include "APIV2Constants.h"

namespace apiv2 
{
	typedef void(*DataParsedCallback)(std::shared_ptr<Packet> parsedPacket, void* callbackObject);
	typedef void(*ProtocolErrorOccurredCallback)(ErrorCode errorCode, void* callbackObject);

	class APIV2PROCESSOR_API APIV2Processor
	{
	public:
		APIV2Processor();
		void processRawData(const std::vector<uint8_t> data);
		void setDataParsedCallback(DataParsedCallback callback, void* callbackObject);
		void setProtocolErrorOccurredCallback(ProtocolErrorOccurredCallback callback, void* callbackObject);
		std::shared_ptr<std::vector<uint8_t>> encodePacket(Packet packet);

		enum State 
		{
			waitingForSop = 0,
			waitingForEop = 1
		};

	private:
		DataParsedCallback _dataParsedCallback;
		void* _dataParsedCallbackObject;
		ProtocolErrorOccurredCallback _protocolErrorOccurredCallback;
		void* _protocolErrorOccurredObject;
		State _state = State::waitingForSop;
		bool _escaped = false;
		uint8_t _runningChecksum;
		std::vector<uint8_t> _dataBuffer;
		bool _errorReportingUnlocked = false;
		uint8_t _currentSequenceNumber = 0x00;

		//static std::shared_ptr<ParsedPacket> parseData(const std::vector<uint8_t> data);
		void invokeParsedCallback(std::shared_ptr<Packet> parsedPacket);
		void invokeProtocolErrorCallback(ErrorCode errorCode);
		void processByte(uint8_t b);
		void reset();
		std::shared_ptr<Packet> generateErrorPacket(ErrorCode errorCode);
	};

	
}