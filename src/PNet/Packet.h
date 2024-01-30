#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <winsock.h>  //for htonl/htons
#else
#include <arpa/inet.h>  //for htonl/htons
#endif

#include <string>
#include <vector>
#include "PacketException.h"
#include "PacketType.h"

namespace PNet
{
	class Packet
	{
	public:
		Packet(PacketType packetType = PacketType::PT_Invalid);
		PacketType GetPacketType();
		void AssignPacketType(PacketType packetType);

		void Clear();
		void Append(const void* data, uint32_t size);

		Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t& data);

		Packet& operator << (const std::string& data);
		Packet& operator >> (std::string& data);

		uint32_t extractionOffset = 0;
		std::vector<char> buffer;
	};
}