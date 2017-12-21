// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/tcp_connection.h>
#include <yarpc/base/logging.h>
namespace yarpc {
namespace core {
TcpConnection::TcpConnection(EventLoop* loop,
    const std::string& name,
    int sockfd,
    const Address& local_addr,
    const Address& peer_addr) :
  _name(name),
  _socket(new Socket(sockfd)),
  _channel(new Channel(loop, sockfd)),
  _local_addr(local_addr),
  _peer_addr(peer_addr) {
    if (loop != NULL) {
      _loop = loop;
    }
}
} // namespace core
} // namespace yarpc
