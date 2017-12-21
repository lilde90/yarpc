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
  _state(Connecting),
  _name(name),
  _reading(true),
  _socket(new Socket(sockfd)),
  _channel(new Channel(loop, sockfd)),
  _local_addr(local_addr),
  _peer_addr(peer_addr) {
    if (loop != NULL) {
      _loop = loop;
    }
    _channel->setReadCallback(std::bind(&TcpConnection::handleRead, this));
    _channel->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    _channel->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    _channel->setErrorCallback(std::bind(&TcpConnection::handleError, this));
    _socket->setKeepAlive(true);
}

TcpConnection::~TcpConnection() {
  if (_socket != NULL) {
    delete _socket;
    _socket = NULL;
  }
  if (_channel != NULL) {
    delete _channel;
    _channel = NULL;
  }
}


void TcpConnection::send(const void* data, int size) {
}

void TcpConnection::send(std::string& message) {
}

void TcpConnection::startRead() {
}

void TcpConnection::stopRead() {
}

void TcpConnection::handleRead() {
}
void TcpConnection::handleWrite() {
}
void TcpConnection::handleClose() {
  _state = Disconnected;
  _channel->disableAll();
  
}
void TcpConnection::handleError() {
}
} // namespace core
} // namespace yarpc
