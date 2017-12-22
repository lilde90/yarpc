// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/tcp_server.h>
#include <yarpc/base/logging.h>
namespace yarpc {
namespace core {

TcpServer::TcpServer(EventLoop* loop,
    const Address& listen_addr,
    const std::string& name):
  _loop(loop),
  _name(name),
  _acceptor(new Acceptor(loop, listen_addr)),
  _thread_pool(new EventLoopThreadPool(loop, _name)),
  _next_conn_id(1) {
    _acceptor->setNewConnectionCallback(
        std::bind(&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
  }

TcpServer::~TcpServer() {
  for (auto it = _connections.begin(); it != _connections.end(); ++it) {
    TcpConnection* conn = it->second;
    if (conn != NULL) {
      delete conn;
    }
    //conn->getLoop()->runInLoop()
  }
  if (_loop != NULL) {
    delete _loop;
  }

  if(_acceptor != NULL) {
    delete _acceptor;
  }
}

void TcpServer::setThreadNum(int num_threads) {
  _thread_pool->setThreadNum(num_threads);
}

void TcpServer::start() {
  _thread_pool->start(_thread_init_callback);
  _loop->runInLoop(std::bind(&Acceptor::listen, _acceptor));
}

void TcpServer::newConnection(int sockfd, const Address& peer_addr) {
  EventLoop* io_loop = _thread_pool->getNextLoop();
  char buf[64];
  snprintf(buf, sizeof(buf), "%s-%d", _name.c_str(), _next_conn_id);
  ++_next_conn_id;
  std::string conn_name = buf;

  Address local_addr(yarpc::core::getLocalAddr(sockfd));
  TcpConnection* conn = new TcpConnection(io_loop,
      conn_name, sockfd, local_addr, peer_addr);
  _connections[conn_name] = conn;
  conn->setConnectionCallback(_connection_callback);
  conn->setMessageCallback(_message_callback);
}

} // namespace core
} // namespace yarpc
