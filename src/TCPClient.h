#pragma once
#include <cstdint>
#include <string>

#ifdef _WIN32 // Windows NT
#include <WinSock2.h>
#include <ws2tcpip.h>
// #define _WIN32_WINNT 0x501
#define PLATFORM_SOCKET SOCKET
#define PLATFORM_ADDRESS struct addrinfo
#else // *nix
#define PLATFORM_SOCKET int
#define PLATFORM_ADDRESS struct sockaddr_in
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
  long timeout_ms;
  /// @param dInitial Is the connection innitial, for debug message
  void Retry(bool dInitial = false);
  void LostConnection();
  std::string _host;
  uint16_t _port;
  PLATFORM_SOCKET _socket;
  PLATFORM_ADDRESS _address;

public:
  static std::string ResolveIP(std::string host);

  /// @deprecated used by the useless TCPServer (C++ seems to not be the best in this)
  TCPClient(PLATFORM_SOCKET socket, PLATFORM_ADDRESS address);
  /// @param host Either domain or IP
  TCPClient(std::string host, uint16_t port, long timeout_ms = 5000, bool debug = false);
  TCPClient(const TCPClient& other);
  ~TCPClient();
  std::string GetHost() const;
  uint16_t GetPort() const;

  /// @brief Acquires data through net. Keeps waiting, until the data is received. Automatically deletes the dynamic buffer. Interprets 1-length data with 0 as
  /// empty
  /// @returns Data string
  std::string ReceiveData();
  /// @brief Acquires data through net. Keeps waiting, until the data is received
  /// @returns Dynamic char buffer
  char* ReceiveRawData(size_t* sz = nullptr);

  /// @brief "Raw" send function
  /// @returns true if data was sent successfully
  bool SendData(const char* data, size_t size);
  /// Sends data
  /// @returns True if data was sent successfully, false otherwise
  bool SendData(std::string data);
};