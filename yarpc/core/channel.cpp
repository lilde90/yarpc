// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
//
#include <yarpc/base/logging.h>
#include <yarpc/core/channel.h>
#include <sys/epoll.h>
#include <poll.h>

namespace yarpc {
namespace core {

void Channel::handleEvent() {
  if (_revents &  POLLNVAL) {
    //LOG_WARNING("%s", "handleEvent event POLLNVAL");
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

} // namespace core
} // namespace yarpc
