#pragma once
#include <cstdint>
#include <string>
#ifdef _WIN32 // Windows NT
    #include <WinSock2.h>
#else // *nix
    #include <netinet/in.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

/// @brief An automatically reconnecting TCP client
class TCPClient {
public:
    static constexpr uint16_t buffer_size = 4096;
private:
	char buffer[buffer_size];
	bool debug;
	void Retry();
	void LostConnection();
	std::string _host;
	uint16_t _port;
#ifdef _WIN32 // Windows NT
	SOCKET socket;
	SOCKADDR_IN address;
public:
	TCPClient(SOCKET socket, SOCKADDR_IN address);
#else // *nix
	int _socket;
	struct sockaddr_in address;
public:
	TCPClient(int socket, struct sockaddr_in address);
	TCPClient(std::string host, uint16_t port, bool debug = false);
#endif
	TCPClient(const TCPClient& other);
	~TCPClient();
	uint32_t GetHost() const;
	uint16_t GetPort() const;

	/// @brief Acquires data through net. Keeps waiting, until the data is received. Automatically deletes the dynamic buffer
	/// @returns Data string
	std::string ReceiveData();
	/// @brief Acquires data through net. Keeps waiting, until the data is received
	/// @returns Dynamic char buffer
	char* ReceiveRawData(size_t* sz = nullptr);

	bool SendData(const char* data, size_t size);
	bool SendData(std::string data);
};