// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/connector.h>
#include <yarpc/base/logging.h>
#include <yarpc/core/socket.h>
//#include <bind>

namespace yarpc {
namespace core {

Connector::Connector(EventLoop* loop, const Address& addr)
  :_loop(loop),
  _server_address(addr),
  _connect(false),
  _state(Disconnected) {
}

Connector::~Connector() {
  if (_channel != NULL) {
    delete _channel;
  }
}

void Connector::start() {
  _connect = true;
}

void Connector::startInLoop() {
  if (_connect) {
    connect();
  }
}

void Connector::stop() {
  _connect = false;
}

void Connector::stopInLoop() {
  if (_state == Connecting) {
    setState(Disconnected);
  }
}

void Connector::connect() {
  int sockfd = yarpc::core::create(_server_address.family());
  int ret = yarpc::core::connect(sockfd, _server_address.getSockAddr());
  int saved_errno = (ret == 0) ? 0 : errno;
  switch(saved_errno) {
    case 0:
    case EINPROGRESS:
    case EINTR:
    case EISCONN:
      connecting(sockfd);
      break;
    case EAGAIN:
    case EADDRINUSE:
    case EADDRNOTAVAIL:
    case ECONNREFUSED:
    case ENETUNREACH:
      retry(sockfd);
      break;

    case EACCES:
    case EPERM:
    case EAFNOSUPPORT:
    case EALREADY:
    case EBADF:
    case EFAULT:
    case ENOTSOCK:
      LOG_ERROR("connect error %d", saved_errno);
      yarpc::core::close(sockfd);
      break;
    default:
      LOG_ERROR("unexpected error %d", saved_errno);
      yarpc::core::close(sockfd);
      break;
  }
}

void Connector::restart() {
  setState(Disconnected);
  _connect = true;
  startInLoop();
}

void Connector::connecting(int sockfd) {
  setState(Connecting);
  _channel = new Channel(_loop, sockfd);
  _channel->setWriteCallback(std::bind(&Connector::handleWrite, this));
  _channel->setErrorCallback(std::bind(&Connector::handleError, this));
  _channel->enableWriting();
}

int Connector::removeChannel() {
  _channel->disableAll();
  //_channel->remove();
  int sockfd = _channel->fd();
  return sockfd;
}

void Connector::resetChannel() {

}

void Connector::handleWrite() {
  if (_state == Connecting) {
    int sockfd = removeChannel();
    setState(Connected);
    if (_connect) {
      _new_connection_callback(sockfd);
    } else {
      yarpc::core::close(sockfd);
    }
  } else {
    if (_state != Disconnected) {
      LOG_FATAL("%s", "connector state is not right");
    }
  }
}

void Connector::handleError() {
  if (_state == Connecting) {
    int sockfd = removeChannel();
    retry(sockfd);
  }
}


void Connector::retry(int sockfd) {
  yarpc::core::close(sockfd);
  setState(Disconnected);
  if (_connect) {
    // retry
  } else {
  }
}

} // namespace core
} // namespace yarpc
