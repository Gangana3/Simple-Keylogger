#include "SocketLogger.h"


void SocketLogger::InitializeWinsock() {
	// Initialize Winsock
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void SocketLogger::DisposeWinsock() {
	WSACleanup();
}

void SocketLogger::Connect(SOCKET sock, string ipv4, int port) {
	// Build the server address
	sockaddr_in address;
	inet_pton(AF_INET, ipv4.c_str(), &address.sin_addr);
	address.sin_port = htons(port);
	address.sin_family = AF_INET;

	// Connect remote server
	connect(sock, (sockaddr*)&address, sizeof(address));
}

SocketLogger::SocketLogger(string ipv4, int port) {
	SocketLogger::InitializeWinsock();
	this->connSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SocketLogger::Connect(this->connSock, ipv4, port);
}

SocketLogger::~SocketLogger() {
	closesocket(this->connSock);
	SocketLogger::DisposeWinsock();
}

void SocketLogger::Write(wstring output) {
	char* buffer = (char*)output.c_str();
	send(this->connSock, buffer, output.length() * 2 + 2, NULL);
}

void SocketLogger::Write(WCHAR output) {
	this->Write(wstring(1, output));
}