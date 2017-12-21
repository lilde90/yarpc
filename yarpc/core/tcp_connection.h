// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_TCP_CONNECTION_H_
#define _YARPC_YARPC_CORE_TCP_CONNECTION_H_

#include <yarpc/core/address.h>
#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <yarpc/core/socket.h>

namespace yarpc {
namespace core {
class TcpConnection {
public:
  TcpConnection(EventLoop* loop,
      const std::string& name,
      int sockfd,
      const Address& local_addr,
      const Address& peer_addr);
  ~TcpConnection();
private:
  EventLoop* _loop;
  const std::string _name;
  bool _reading;
  Socket* _socket;
  Channel* _channel;
  const Address _local_addr;
  const Address _peer_addr;
};
} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_TCP_CONNECTION_H_
