#ifndef SOCKET_H
#define SOCKET_H

//NOTE: You must call AS_Startup() before using this library.

/* Example (server): To create a server, you have to:
1. Create a socket by calling AS_CreateSocket(), the default protocol is TCP(SOCK_STREAM). If you'd like to use UDP, specify SOCK_DGRAM for the type parameter instead.

2. Set the socket address by calling AS_InitSocketAddr(), you can specify a custom port number but the IP should remain 0.

3. Bind the socket by calling AS_BindSocket()

4. To receive data from a specific address, call AS_ReceiveFrom(). The AS_ReceiveFrom() function writes the receive data into the 'Buffer' parameter and returns AS_ReceiveResult which contains the sender address, the address size and the bytes received. 
*/

/* Example (Client): To create a client, you have to:
1. Create a socket by calling AS_CreateSocket(), the default protocol is TCP(SOCK_STREAM). If you'd like to use UDP, specify SOCK_DGRAM for the type parameter instead.

2. Set the socket address by calling AS_InitSocketAddr(), specify a port number and IP address.

3. To send data to a specific address, call AS_Sendto(). The AS_Sendto() function sends the input data to a specific address. 
*/

#include "prerequisite.h"

struct AS_SocketAddr
{
	sockaddr _addr;
};

struct AS_Socket
{
	SOCKET s;
};

struct AS_ReceiveResult
{
	AS_SocketAddr Addr;
	int AddrSize;
	int BytesReceived;
};

void AS_Startup();
void AS_Cleanup();

AS_SocketAddr 
AS_InitSocketAddr(uint16_t Port, uint8_t a, uint8_t b, uint8_t c, uint8_t d);

void AS_SetIPv4(AS_SocketAddr* Addr, uint8_t a, uint8_t b, uint8_t c, uint8_t d);
void AS_SetPort(AS_SocketAddr* Addr, uint16_t Port);
uint16_t AS_GetPort(AS_SocketAddr* Addr);

//NOTE: The default protocol is TCP
void AS_InitSocket(AS_Socket* Socket, int Type);
void AS_BindSocket(AS_Socket* Socket, AS_SocketAddr* Addr);
void AS_CloseSocket(AS_Socket* Socket);

void AS_Sendto(AS_Socket* Socket, AS_SocketAddr* Addr, 
			   const char* Buffer, int Len, int Flags);
			   
AS_ReceiveResult 
AS_ReceiveFrom(AS_Socket* Socket, char* Buffer, int BufferSize);

#endif