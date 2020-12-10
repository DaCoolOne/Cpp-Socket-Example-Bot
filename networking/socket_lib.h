#ifndef NETWORKING_SOCKET_LIB_H
#define NETWORKING_SOCKET_LIB_H

#include "../structs/enums.h"

#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <cstdint>
#include <intrin.h>

namespace rlbot {
namespace networking {

const int MAX_CONNECTION_ATTEMPTS = 16;

inline void MakeBlocking(SOCKET &s)
{
  unsigned long ul = 0;
  ioctlsocket(s, FIONBIO, &ul);
}

inline void MakeNonBlocking(SOCKET &s)
{
  unsigned long ul = 1;
  ioctlsocket(s, FIONBIO, &ul);
}

inline bool InitSocket(SOCKET &rlbot_socket)
{
  WSADATA wsa;

  if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
  {
    std::cerr << "Error initializing socket: " << WSAGetLastError() << std::endl;
    return false;
  }
  
  int recv_status;

  if((rlbot_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    std::cerr << "Error initializing socket: " << WSAGetLastError() << std::endl;
    return false;
  }

  return true;
}

inline bool AttemptConnect(SOCKET rlbot_socket, uint16_t port)
{
  struct sockaddr_in serv_addr;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int connect_status;
  int connect_failure_counter = 0;

  do
  {
    connect_status = connect(rlbot_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    if(connect_status < 0)
    {
      if(connect_failure_counter >= MAX_CONNECTION_ATTEMPTS)
      {
        std::cerr << "Connection failed. Max connection attempts reached. Aborting." << std::endl;
        return false;
      }
      else
      {
        std::cerr << "Connection failed. Trying again..." << std::endl;
        connect_failure_counter ++;
      }
    }
  } while(connect_status < 0);

  return true;
}

inline void MakeHeader(uint8_t * const header_buffer, SEND_PACKET type, uint16_t size)
{
  header_buffer[0] = 0;
  header_buffer[1] = static_cast<uint8_t>(type);

  header_buffer[2] = (size >> 8) & 255;
  header_buffer[3] = (size & 255);
}

} // namespace networking
} // namespace rlbot

#endif