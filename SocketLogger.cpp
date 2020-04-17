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

	connect(sock, (sockaddr*)&address, sizeof(address));
}

SocketLogger::SocketLogger(string ipv4, int port) {
	SocketLogger::InitializeWinsock();
	this->connSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

SocketLogger::~SocketLogger() {
	closesocket(this->connSock);
	SocketLogger::DisposeWinsock();
}

void SocketLogger::Write(string output) {
	send(this->connSock, output.c_str(), output.length(), NULL);
}

void SocketLogger::Write(char output) {
	this->Write(string(1, output));
}