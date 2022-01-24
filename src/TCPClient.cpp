#include "TCPClient.h"

#ifndef _WIN32
    #include <arpa/inet.h>
#endif

//Загружает в буфер данные от клиента и возвращает их размер
bool TCPClient::HasData() { return recv(_socket, buffer, buffer_size, 0) > 0; }
//Возвращает указатель на буфер с данными от клиента
std::string TCPClient::GetData() { return std::string(buffer); }
//Отправляет данные клиенту
bool TCPClient::SendData(std::string data) const {
	if (send(_socket, data.c_str(), sizeof(data.c_str()), 0) < 0)
		return false;
	return true;
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