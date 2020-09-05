#include "AutoSocket.h"

void AS_Startup()
{
	WSADATA WSAData;
	//NOTE: Supports version 2.2 of windows sockets
	WSAStartup(MAKEWORD(2, 2), &WSAData);
}

void AS_SetPort(AS_SocketAddr* Addr, uint16_t Port)
{
	*(uint16_t*)Addr->_addr.sa_data = htons(Port);
}

uint16_t AS_GetPort(AS_SocketAddr* Addr)
{
	return ntohs(*(const uint16_t*)Addr->_addr.sa_data);
}

void AS_SetIPv4(AS_SocketAddr* Addr, uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	Addr->_addr.sa_family = AF_INET;
	Addr->_addr.sa_data[2] = a;
	Addr->_addr.sa_data[3] = b;
	Addr->_addr.sa_data[4] = c;
	Addr->_addr.sa_data[5] = d;
}

AS_SocketAddr 
AS_InitSocketAddr(uint16_t Port, uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	AS_SocketAddr Result = {};
	AS_SetPort(&Result, Port);
	AS_SetIPv4(&Result, a, b, c, d);
	
	return Result;
}

void AS_InitSocket(AS_Socket* Socket, int Type = SOCK_STREAM)
{
	int Protocol = Type == SOCK_STREAM ? IPPROTO_TCP : IPPROTO_UDP;
	Socket->s = socket(AF_INET, Type, Protocol);
	
	if(Socket->s == INVALID_SOCKET)
	{
		printf("Error on creating socket... ERR CODE: %d\n", WSAGetLastError());
	}
	else
	{
		printf("Successfully created socket.\n");
	}
}

void AS_BindSocket(AS_Socket* Socket, AS_SocketAddr* Addr)
{
	if(bind(Socket->s, &Addr->_addr, sizeof(Addr->_addr)) == SOCKET_ERROR)
	{
		printf("Error on binding socket... ERR CODE: %d\n", WSAGetLastError());
	}
	else
	{
		printf("Successfully binded socket.\n");
		printf("Binded port: %u\n", AS_GetPort(Addr));
	}
}

void AS_Sendto(AS_Socket* Socket, AS_SocketAddr* Addr, 
			   const char* Buffer, int Len, int Flags = 0)
{
	if(Len > INT_MAX)
	{
		printf("Error: Data size is too big! \n");
		return;
	}
	
	if(sendto(Socket->s, Buffer, Len, Flags, &Addr->_addr, sizeof(Addr->_addr))
		== SOCKET_ERROR)
	{
		printf("Error on sending data... ERR CODE: %d\n", WSAGetLastError());
	}
}

AS_ReceiveResult 
AS_ReceiveFrom(AS_Socket* Socket, char* Buffer, int BufferSize)
{
	AS_ReceiveResult Result = {};
	Result.AddrSize = sizeof(Result.Addr._addr);
	
	Result.BytesReceived = 
	recvfrom(Socket->s, Buffer, BufferSize, 0, 
			 &Result.Addr._addr, &Result.AddrSize);
			 
	if(Result.BytesReceived == SOCKET_ERROR)
	{
		printf("Error on receiving data... ERR CODE: %d\n", WSAGetLastError());
		return {};
	}
	
	printf("Received: %s\n", Buffer);
	
	return Result;
}

void AS_CloseSocket(AS_Socket* Socket)
{
	closesocket(Socket->s);
}

void AS_Cleanup()
{
	WSACleanup();
}