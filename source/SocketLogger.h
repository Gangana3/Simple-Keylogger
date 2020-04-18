#pragma once

#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")
#include "Logger.h"


/*
	Logs the given output to a socket
*/
class SocketLogger : public Logger
{
private:
	SOCKET connSock;
	
	static void InitializeWinsock();
	static void DisposeWinsock();
	static void Connect(SOCKET sock, string ipv4, int port);

public:
	SocketLogger(string ipv4, int port);
	~SocketLogger();

	virtual void Write(wstring output);
	virtual void Write(WCHAR output);
};

