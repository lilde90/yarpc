// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_CHANNEL_H_
#define _YARPC_YARPC_CORE_CHANNEL_H_

#include <yarpc/core/event_loop.h>
#include <functional>

namespace yarpc {
namespace core {

class EventLoop;

class Channel {
public:
  typedef std::function<void()> EventCallback;

  Channel(EventLoop* loop, int fd);

  int fd() {
    return _fd;
  }
  int events() {
    return _events;
  }
  int revents() {
    return _revents;
  }

  void set_revents(int revents) {
    _revents = revents;
  }

  bool isNoneEvent() const {
    return _events == _k_none_event;
  }
  int index() {
    return _index;
  }
  void set_index(int index) {
    _index = index;
  }

  void enableReading() {
    _events |= _k_read_event;
  }

  void enableWriting() {
    _events |= _k_write_event;
  }

  void disableAll() {
    _events = _k_none_event;
  }

  EventLoop* ownerLoop() {
    return _loop;
  }

  void handleEvent();

  void update();

  void setReadCallback(const EventCallback& cb) {
    _read_call_back = cb;
  }

  void setWriteCallback(const EventCallback& cb) {
    _write_call_back = cb;
  }

  void setErrorCallback(const EventCallback& cb) {
    _error_call_back = cb;
  }
private:
  static const int _k_none_event;
  static const int _k_read_event;
  static const int _k_write_event;

  EventLoop* _loop;
  int _fd;
  int _events;
  int _revents;
  int _index;

  EventCallback _read_call_back;
  EventCallback _write_call_back;
  EventCallback _error_call_back;

};
} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_CHANNEL_H_
