// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_TCP_SERVER_H_
#define _YARPC_YARPC_CORE_TCP_SERVER_H_
#include <string>
#include <yarpc/base/yarpc_defs.h>
#include <yarpc/core/event_loop.h>
#include <yarpc/core/acceptor.h>
#include <yarpc/core/address.h>
#include <yarpc/core/event_loop_thread_pool.h>
#include <yarpc/core/tcp_connection.h>
#include <unordered_map>
#include <functional>
namespace yarpc {
namespace core {
class TcpServer {
public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;
  TcpServer(EventLoop* loop,
      const Address& listen_addr,
      const std::string& name);
  ~TcpServer();
  const std::string& name() const {
    return _name;
  }
  EventLoop* getLoop() const {
    return _loop;
  }
  
  void setThreadNum(int num_threads);
  void setThreadInitCallback(const ThreadInitCallback& cb) {
    _thread_init_callback = cb;
  }

  EventLoopThreadPool* threadPool() {
    return _thread_pool;
  }

  void start();

  void setConnectionCallback(const ConnectionCallback& cb) {
    _connection_callback = cb;
  }

  void setMessageCallback(const MessageCallback& cb) {
    _message_callback = cb;
  }
private:

  EventLoop* _loop;
  const std::string _name;
  Acceptor* _acceptor;
  EventLoopThreadPool* _thread_pool;
  ConnectionCallback _connection_callback;
  MessageCallback _message_callback;
  ThreadInitCallback _thread_init_callback;
  
  int _started;
  std::unordered_map<std::string, TcpConnection*> _connections;
  int _next_conn_id;
private:
  void newConnection(int sockfd, const Address& peer_addr);
};
} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_TCP_SERVER_H_
