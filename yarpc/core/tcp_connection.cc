// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/tcp_connection.h>
#include <yarpc/base/logging.h>
#include <string>
#include <functional>
namespace yarpc {
namespace core {

void defaultConnectionCallback(const TcpConnection* conn) {
  // TODO:implement default connection call back
  LOG_TRACE("default connection callback");
}

void defaultMessageCallback(const TcpConnection* conn, yarpc::base::Buffer* buf) {
  //TODO: implement default message call back
}
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

void TcpConnection::send(const void* data, size_t size) {
  //send(std::string(static_cast<const char*>(data)), size);
}

void TcpConnection::send(const std::string& message) {
  if (_state == Connected) {
    sendInLoop(message);
    //_loop->runInLoop(std::bind(&TcpConnection::sendInLoop, this, std::forward<std::string>(message)));
  }
}

void TcpConnection::send(yarpc::base::Buffer* buf) {
  if (_state == Connected) {
    sendInLoop(buf->peek(), buf->readableSize());
    buf->readAll();
  } else {
    //_loop->runInLoop(std::bind(&TcpConnection::sendInLoop,
    //      this,
    //      buf->readAllAsString());
  }
}

void TcpConnection::sendInLoop(const std::string& message) {
  sendInLoop(static_cast<const void*>(message.data()), message.size());
}

void TcpConnection::sendInLoop(const void* data, size_t len) {
  if (_state == Disconnected) {
    LOG_WARNING("connection Disconnected, no need to send data");
    return;
  }
}

void TcpConnection::startRead() {
  _loop->runInLoop(std::bind(&TcpConnection::startReadInLoop, this));
}

void TcpConnection::startReadInLoop() {
  if (!_reading || !_channel->isReading()) {
    _channel->enableReading();
    _reading = true;
  }
}

void TcpConnection::stopRead() {
  _loop->runInLoop(std::bind(&TcpConnection::stopReadInLoop, this));
}


void TcpConnection::stopReadInLoop() {
  if (_reading || _channel->isReading()) {
    _channel->disableReading();
    _reading = false;
  }
}
void TcpConnection::handleRead() {
  // read from buffer
}
void TcpConnection::handleWrite() {
  // write to buffer;
}
void TcpConnection::handleClose() {
  _state = Disconnected;
  _channel->disableAll();
  
}
void TcpConnection::handleError() {
  // just logging error
}
} // namespace core
} // namespace yarpc
