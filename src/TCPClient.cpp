#include "TCPClient.h"
#include <cstring>
#include <chrono>
#include <thread>

#ifndef _WIN32
	#include <arpa/inet.h>
#endif

char* TCPClient::ReceiveRawData() {
	size_t bufSz;
	// receive the size first
	while (recv(_socket, reinterpret_cast<char*>(&bufSz), sizeof(size_t), 0) < 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	char* buf = new char[bufSz];
	memset(buf, 0, bufSz);
	// receive data of the actual size
	while (recv(_socket, buf, bufSz, 0) < 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	return buf;
}
std::string TCPClient::ReceiveData() {
	char* buf = ReceiveRawData();
	std::string rs = buf;
	delete[] buf;
	return rs;
}
//Отправляет данные клиенту
bool TCPClient::SendData(const void* data, size_t size) const {
	return send(_socket, data, size, 0) >= 0;
}
bool TCPClient::SendData(std::string data) const {
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
	TCPClient::TCPClient(std::string host, uint16_t port) {
		_socket = socket(AF_INET, SOCK_STREAM, 0);
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		inet_pton(AF_INET, host.c_str(), &address.sin_addr);
		connect(_socket, (struct sockaddr*)&address, sizeof(address));
	}

	TCPClient::~TCPClient() {
		shutdown(_socket, 0); //Обрыв соединения сокета
		close(_socket);		 //Закрытие сокета
	}

	// Геттеры хоста и порта
	uint32_t TCPClient::GetHost() const { return address.sin_addr.s_addr; }
	uint16_t TCPClient::GetPort() const { return address.sin_port; }
#endif