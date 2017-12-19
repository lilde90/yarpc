// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
//
#include <yarpc/base/logging.h>
#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <sys/epoll.h>
#include <poll.h>

namespace yarpc {
namespace core {

const int Channel::_k_none_event = 0;
const int Channel::_k_read_event = POLLIN | POLLPRI;
const int Channel::_k_write_event = POLLOUT;

void Channel::handleEvent() {
  if (_revents &  POLLNVAL) {
    //LOG_WARNING("handleEvent event POLLNVAL");
  }

  if (_revents & (POLLERR | POLLNVAL)) {
    if (_error_call_back) {
      _error_call_back();
    }
  }

  if (_revents & (POLLIN | POLLPRI | POLLRDHUP)) {
    if (_read_call_back) {
      _read_call_back();
    }
  }

  if (_revents & (POLLOUT)) {
    if (_write_call_back) {
      _write_call_back();
    }
  }
}

Channel::Channel(EventLoop* loop, int fd) 
  :_loop(loop),
  _fd(fd),
  _events(0),
  _revents(0) {
}

void Channel::update() {
  _loop->updateChannel(this);
}

} // namespace core
} // namespace yarpc
