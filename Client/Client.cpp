#include "Client.h"
#include <iostream>

bool Client::Connect(IPEndpoint ip)
{
	isConnected = false;
	if (PNet::Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
		socket = PNet::Socket(ip.GetIPVersion());
		if (socket.Create() == PNet::PResult::P_Success)
		{
			if (socket.SetBlocking(true) != PResult::P_Success)
				return false;

			std::cout << "Socket successfully created." << std::endl;
			if (socket.Connect(ip) == PNet::PResult::P_Success)
			{
				isConnected = true;
				std::cout << "Successfully connected to server!" << std::endl;
				return true;
				
			}
			else
			{
				std::cerr << "Failed to connect to server." << std::endl;
			}
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to created." << std::endl;
		}
	}
	return false;
}

bool Client::IsConnected()
{
    return isConnected;
}

bool Client::Frame()
{
	PNet::Packet stringPacket(PNet::PacketType::PT_ChatMessage);
	stringPacket << std::string("This is my string packet!");

	PNet::Packet integersPacket(PNet::PacketType::PT_IntegerArray);
	uint32_t arraySize = 6;
	uint32_t integerArray[6] = { 2, 5, 7, 1, 2, 9 };
	integersPacket << arraySize;
	for (auto integer : integerArray)
	{
		integersPacket << integer;
	}

	PNet::PResult result;

	if (rand() % 2 == 0)
	{
		result = socket.Send(stringPacket);
	}
	else
	{
		result = socket.Send(integersPacket);
	}
	if (result != PNet::PResult::P_Success)
	{
		isConnected = false;
		return false;
	}

	std::cout << "Attempting to send chunk of data..." << std::endl;
	Sleep(500);
	return true;
	
}