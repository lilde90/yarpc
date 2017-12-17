// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include<yarpc/core/event_loop.h>
#include<yarpc/core/event_loop_thread.h>
#include<yarpc/core/event_loop_thread_pool.h>
#include <yarpc/base/logging.h>
#include<stdio.h>


namespace yarpc {
namespace core {

EventLoopThreadPool::EventLoopThreadPool(EventLoop* base_loop, const std::string& name)
  :_base_loop(base_loop),
  _name(name),
  _started(false),
  _thread_num(0),
  _next(0) {
}

EventLoopThreadPool::~EventLoopThreadPool() {
}

void EventLoopThreadPool::start(const ThreadInitCallback& cb) {
  _started = true;
  for(int i = 0; i < _thread_num; i++) {
    char buf[_name.size() + 32] = {0};
    snprintf(buf, sizeof(buf), "%s%d", _name.c_str(), i);
    EventLoopThread* t = new EventLoopThread(cb, buf);
    _threads.push_back(t);
    _loops.push_back(t->startLoop());
  }

  if (_thread_num == 0 && cb) {
    cb(_base_loop);
  }
}

EventLoop* EventLoopThreadPool::getNextLoop() {
  if (!_started) {
    LOG_FATAL("%s", "event loop thread pool not started");
  }
  EventLoop* loop = _base_loop;
  if (!_loops.empty()) {
    loop = _loops[_next];
    ++_next;
    if (static_cast<size_t>(_next) >= _loops.size()) {
      _next = 0;
    }
  }
  return loop;
}

EventLoop* EventLoopThreadPool::getHashLoop(size_t hash_code) {
  if (!_started) {
    LOG_FATAL("%s", "event loop thread pool not started");
  }
  EventLoop* loop = _base_loop;
  if (!_loops.empty()) {
    loop = _loops[hash_code % _loops.size()];
  }
  return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops() {
  if (!_started) {
    LOG_FATAL("%s", "event loop thread pool not started");
  }
  if (_loops.empty()) {
    return std::vector<EventLoop*>(1, _base_loop);
  } else {
    return _loops;
  }
}

} // namespace core
} // namespace yarpc
