#pragma once
#include "SocketHandle.h"
#include "PResult.h"
#include "IPVersion.h"
#include "SocketOption.h"
#include "IPEndpoint.h"
#include "Constants.h"
#include "Packet.h"

namespace PNet
{
	class Socket
	{
	public:
		Socket(IPVersion ipversion = IPVersion::IPv4,
			SocketHandle handle = INVALID_SOCKET);

		PResult Create();
		PResult Close();
		PResult Bind(IPEndpoint endpoint);
		PResult Listen(IPEndpoint endpoint, int backlog = 5);
		PResult Accept(Socket& outSocket);
		PResult Connect(IPEndpoint endpoint);
		PResult Send(const void* data, int numberOfBytes, int& bytesSent);
		PResult Recv(void* destionation, int numberOfBytes, int& bytesReceived);
		PResult SendAll(const void* data, int numberOfBytes);
		PResult RecvAll(void* destionation, int numberOfBytes);
		PResult Recv(Packet& packet);
		PResult Send(Packet& packet);
		SocketHandle GetHandle();
		IPVersion GetIPVersion();
	private:
		PResult SetSocketOption(SocketOption option, BOOL value);
		IPVersion ipversion = IPVersion::IPv4;
		SocketHandle handle = INVALID_SOCKET;

	};
}