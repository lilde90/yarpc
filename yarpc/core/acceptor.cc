// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/acceptor.h>
#include <yarpc/base/logging.h>
namespace yarpc {
namespace core {

Acceptor::Acceptor(EventLoop* loop, const Address listen_addr) 
  :_loop(loop),
  _accept_socket(create(listen_addr.family())),
  _accept_channel(loop, _accept_socket.fd()),
  _listening(false) {
    _accept_socket.setReuseAddr(true);
    _accept_socket.setReusePort(true);
    _accept_socket.bind(listen_addr);

    _accept_channel.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor() {
  _accept_channel.disableAll();
}

void Acceptor::listen() {
  _listening = true;
  _accept_socket.listen();
  _accept_channel.enableReading();
}

void Acceptor::handleRead() {
  Address peer_addr;
  int connfd = _accept_socket.accept(&peer_addr);
  if (connfd >= 0) {
    if(_newConnectionCallback) {
      _newConnectionCallback(connfd, peer_addr);
    } else {
      yarpc::core::close(connfd);
    }
  } else {
    LOG_ERROR("%s", "acceptor handle read failed");
  }

}
} // namespace core
} // namespace yarpc
