// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/acceptor.h>
namespace yarpc {
namespace core {

Acceptor::Acceptor(EventLoop* loop/*, const InetAddress listen_addr*/) 
  :_loop(loop),
  _accept_channel(loop, 0),
  _listening(false) {

  _accept_channel.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

void Acceptor::listen() {
  _listening = true;
  _accept_channel.enableReading();
}

void Acceptor::handleRead() {

}
} // namespace core
} // namespace yarpc
