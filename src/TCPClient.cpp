#include "TCPClient.h"
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>
#include "Utils.h"
using namespace std;

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")
#else
#include <netdb.h>
#include <arpa/inet.h>
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#ifdef _WIN32
void WSInit() {
	WSADATA data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0) {
		fputs("Could not initialise Winsock.\n", stderr);
		exit(1);
	}
}
namespace PLATFORM {
	void CloseConnection(PLATFORM_SOCKET& socket) {
		WSACleanup();
		if (socket == INVALID_SOCKET)
			return;
		shutdown(socket, 0);
		closesocket(socket);
		socket = INVALID_SOCKET;
	}
	void OpenConnection(PLATFORM_SOCKET& _socket, PLATFORM_ADDRESS& hints, std::string ip, uint16_t port) {
		WSInit();
		int iResult;
		PLATFORM_ADDRESS* addrinfo = nullptr;
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		
		if (iResult = getaddrinfo(ip.c_str(), Utils::String::Convert(port).c_str(), &hints, &addrinfo)) {
			CloseConnection(_socket);
			return;
		}
		_socket = socket(addrinfo->ai_family, addrinfo->ai_socktype, addrinfo->ai_protocol);
		if (_socket == INVALID_SOCKET) {
			CloseConnection(_socket);
			return;
		}
		if ((iResult = connect(_socket, addrinfo->ai_addr, (int)addrinfo->ai_addrlen)) == SOCKET_ERROR)
			CloseConnection(_socket);
		freeaddrinfo(addrinfo);
	}
	size_t Recv(PLATFORM_SOCKET socket, char* buf, int buf_sz, int flags) {
		return recv(socket, buf, buf_sz, flags);
	}
	int __stdcall Send(PLATFORM_SOCKET socket, char* buf, int buf_sz, int flags) {
		return send(socket, buf, buf_sz, flags);
	}
}
#else
namespace PLATFORM {
	void CloseConnection(PLATFORM_SOCKET& socket) {
		shutdown(socket, 0);
		close(socket);
		socket = INVALID_SOCKET;
	}
	void OpenConnection(PLATFORM_SOCKET& _socket, PLATFORM_ADDRESS& address, std::string ip, uint16_t port) {
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		inet_pton(AF_INET, ip.c_str(), &address.sin_addr);
		connect(_socket, (struct sockaddr*)&address, sizeof(address));
	}
	ssize_t Recv(PLATFORM_SOCKET socket, void* buf, size_t buf_sz, int flags) {
		return recv(socket, buf, buf_sz, flags);
	}
	ssize_t Send(PLATFORM_SOCKET socket, void* buf, size_t buf_sz, int flags) {
		return send(socket, buf, buf_sz, flags);
	}
}
#endif


void TCPClient::Retry(bool dInitial) {
	if (_socket != INVALID_SOCKET)
		return;
	if (debug) {
		if (dInitial)
			printf("Connecting...\n");
		else
			printf("Retrying...\n");
	}
	PLATFORM::OpenConnection(_socket, _address, ResolveIP(_host), _port);
}
void TCPClient::LostConnection() {
	PLATFORM::CloseConnection(_socket);
	if (debug)
		printf("Connection lost\n");
}
char* TCPClient::ReceiveRawData(size_t* sz) {
	Retry(false);
	size_t bufSz;
	// receive the size first
	if (PLATFORM::Recv(_socket, reinterpret_cast<char*>(&bufSz), sizeof(size_t), 0) == SOCKET_ERROR) {
		LostConnection();
		return nullptr;
	}
	char* buf = new char[bufSz + 1];
	memset(buf, 0, bufSz + 1);
	// receive data of the actual size
	if (PLATFORM::Recv(_socket, buf, bufSz, 0) == SOCKET_ERROR) {
		LostConnection();
		return nullptr;
	}
	if (sz)
		*sz = bufSz;
	return buf;
}
std::string TCPClient::ReceiveData() {
	size_t sz;
	char* buf = ReceiveRawData(&sz);
	if (!buf)
		return "";
	std::string rs = (sz == 1 && *buf == 0) ? "" : std::string(buf, sz);
	delete[] buf;
	return rs;
}
bool TCPClient::SendData(const char* data, size_t size) {
	Retry(false);
	size_t offset = 0, sent;
	while (offset < size)
		if ((sent = PLATFORM::Send(_socket, const_cast<char*>(data + offset), size - offset, MSG_NOSIGNAL)) == (size_t)SOCKET_ERROR) {
			LostConnection();
			return false;
		}
		else
			offset += sent;
	return true;
}
bool TCPClient::SendData(std::string data) {
	return SendData(data.c_str(), data.length());
}
TCPClient::TCPClient(PLATFORM_SOCKET socket, PLATFORM_ADDRESS address) : _socket(socket), _address(address) {}
TCPClient::TCPClient(const TCPClient& other) : TCPClient(other._host, other._port, other.debug) {}
TCPClient::TCPClient(std::string host, uint16_t port, bool debug) {
	this->debug = debug;
	_socket = INVALID_SOCKET;
	_host = host;
	_port = port;
	Retry(true);
}

TCPClient::~TCPClient() {
	PLATFORM::CloseConnection(_socket);
}

std::string TCPClient::GetHost() const { return _host; }
uint16_t TCPClient::GetPort() const { return _port; }

std::string TCPClient::ResolveIP(std::string host) {
#ifdef _WIN32
	WSInit();
#endif
	struct hostent* he = gethostbyname(host.c_str());
	if (he == NULL)
		switch (h_errno) {
		case HOST_NOT_FOUND:
			fputs("The host was not found.\n", stderr);
			return "";
		case NO_ADDRESS:
			fputs("The name is valid but it has no address.\n", stderr);
			return "";
		case NO_RECOVERY:
			fputs("A non-recoverable name server error occurred.\n", stderr);
			return "";
		case TRY_AGAIN:
			fputs("The name server is temporarily unavailable.", stderr);
			return "";
		}
	std::string result = inet_ntoa(*((struct in_addr*)he->h_addr_list[0]));
#ifdef _WIN32
	WSACleanup();
#endif
	return result;
}