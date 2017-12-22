// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_TCP_CLIENT_H_
#define _YARPC_YARPC_CORE_TCP_CLIENT_H_

#include <yarpc/base/mutex_lock.h>
#include <yarpc/base/yarpc_defs.h>
#include <yarpc/core/tcp_client.h>
#include <yarpc/core/tcp_connection.h>
#include <yarpc/core/connector.h>
#include <yarpc/core/event_loop.h>

namespace yarpc {
namespace core {
class TcpClient {
public:
  TcpClient(EventLoop* loop,
    const Address& serverAddr,
    const std::string& name);

  ~TcpClient();

  void connect();
  void disconnect();
  void stop();
  EventLoop* getLoop() const {
    return _loop;
  }
  const std::string& name() const {
    return _name;
  }

  void setConnectionCallback(const ConnectionCallback& cb) {
    _connection_callback = cb;
  }
  void setMessageCallback(const MessageCallback& cb) {
    _message_callback = cb;
  }

private:
  EventLoop* _loop;
  Connector* _connector;
  std::string _name;
  ConnectionCallback _connection_callback;
  MessageCallback _message_callback;
  bool _connect;

  TcpConnection* _connection;
  mutable yarpc::base::MutexLock _mutex;

private:
  void newConnection(int sockfd);

};
} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_TCP_CLIENT_H_
