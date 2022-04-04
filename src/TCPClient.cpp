#include "TCPClient.h"
#include <cstring>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

#ifndef _WIN32
	#include <arpa/inet.h>
#endif

void TCPClient::Retry() {
	if (_socket)
		return;
	if (debug)
		printf("Retrying...\n");
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons(_port);
	inet_pton(AF_INET, _host.c_str(), &address.sin_addr);
	connect(_socket, (struct sockaddr*)&address, sizeof(address));
}
void TCPClient::LostConnection() {
	close(_socket);
	_socket = 0;
	if (debug)
		printf("Connection lost\n");
}
char* TCPClient::ReceiveRawData(size_t* sz) {
	Retry();
	size_t bufSz;
	ssize_t code;
	// receive the size first
	while ((code = recv(_socket, reinterpret_cast<char*>(&bufSz), sizeof(size_t), 0)) < 1) {
		if (code < 0) {
			if (sz) *sz = 0;
			LostConnection();
			return nullptr;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	char* buf = new char[bufSz + 1];
	memset(buf, 0, bufSz + 1);
	// receive data of the actual size
	while ((code = recv(_socket, buf, bufSz, 0)) < 1) {
		if (code < 0) {
			if (sz) *sz = 0;
			LostConnection();
			return nullptr;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	if (sz)
		*sz = bufSz;
	return buf;
}
std::string TCPClient::ReceiveData() {
	char* buf = ReceiveRawData();
	if (!buf)
		return "";
	std::string rs = buf;
	delete[] buf;
	return rs;
}
//Отправляет данные клиенту
bool TCPClient::SendData(const char* data, size_t size) {
	Retry();
	size_t offset = 0, sent;
	while (offset < size)
		if ((sent = send(_socket, data + offset, size - offset, MSG_NOSIGNAL)) == (size_t)-1) {
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

#ifdef _WIN32
	// Конструктор клиента по сокету и адресу
	TCPClient::TCPClient(SOCKET socket, SOCKADDR_IN address) : socket(socket), address(address) {}
	// Конструктор копирования
	TCPClient::TCPClient(const TCPClient& other) : socket(other.socket), address(other.address) {}

	TCPClient::~Client() {
		shutdown(socket, 0); //Обрыв соединения сокета
		closesocket(socket); //Закрытие сокета
	}

	// Геттеры хоста и порта
	uint32_t TCPClient::GetHost() const { return address.sin_addr.S_un.S_addr; }
	uint16_t TCPClient::GetPort() const { return address.sin_port; }
#else // *nix
	// Конструктор клиента по сокету и адресу
	TCPClient::TCPClient(int socket, struct sockaddr_in address) : _socket(socket), address(address) {}
	// Конструктор копирования
	TCPClient::TCPClient(const TCPClient& other) : _socket(other._socket), address(other.address) {}
	TCPClient::TCPClient(std::string host, uint16_t port, bool debug) {
		this->debug = debug;
		_socket = 0;
		_host = host;
		_port = port;
		Retry();
	}

	TCPClient::~TCPClient() {
		shutdown(_socket, 0); //Обрыв соединения сокета
		close(_socket);		 //Закрытие сокета
	}

	// Геттеры хоста и порта
	uint32_t TCPClient::GetHost() const { return address.sin_addr.s_addr; }
	uint16_t TCPClient::GetPort() const { return address.sin_port; }
#endif