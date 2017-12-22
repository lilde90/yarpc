// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/tcp_client.h>
#include <yarpc/base/logging.h>
#include <yarpc/core/connector.h>
#include <functional>
namespace yarpc {
namespace core {
TcpClient::TcpClient(EventLoop* loop,
    const Address& serverAddr,
    const std::string& name) {
  _connector->setNewConnectionCallback(
      std::bind(&TcpClient::newConnection, this, std::placeholders::_1));
}

TcpClient::~TcpClient() {
  TcpConnection* conn = NULL;
  {
    yarpc::base::MutexLockGuard lock(_mutex);
    conn = _connection;
  }
  if (conn != NULL) {
  }
}

void TcpClient::connect() {
  LOG_INFO("TcpClient connect %s", _name.c_str());
  _connect = true;
  _connector->start();
}

void TcpClient::disconnect() {
  _connect = false;
  {
    yarpc::base::MutexLockGuard lock(_mutex);
    if (_connection != NULL) {
    }
  }
}

void TcpClient::stop() {
  _connect = false;
  _connector->stop();
}


void TcpClient::newConnection(int sockfd) {
  Address peer_addr(yarpc::core::getPeerAddr(sockfd));
  Address local_addr(yarpc::core::getLocalAddr(sockfd));
  TcpConnection* conn = new TcpConnection(_loop, _name, sockfd, local_addr, peer_addr);
  conn->setConnectionCallback(_connection_callback);
  conn->setMessageCallback(_message_callback);
  {
    yarpc::base::MutexLockGuard lock(_mutex);
    _connection = conn;
  }
}

} // namespace core
} // namespace yarpc
