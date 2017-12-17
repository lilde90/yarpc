// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/base/mutex_lock.h>
#include <yarpc/core/event_loop_thread.h>
#include <yarpc/core/event_loop.h>

namespace yarpc {
namespace core {

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb, std::string& name)
  :_loop(NULL),
  _exiting(false),
  _thread(std::bind(&EventLoopThread::threadFunc, this), name),
  _mutex(),
  _cond(_mutex),
  _callback(cb) {
}

EventLoopThread::~EventLoopThread() {
  _exiting = true;
  if (_loop != NULL) {
    //_loop->quit();
    _thread.join();
  }
}

EventLoop* EventLoopThread::startLoop() {
  _thread.start();
  {
    MutexLockGuard lock(_mutex);
    while(_loop == NULL) {
      _cond.wait();
    }
  }
  return _loop;
}


void EventLoopThread::threadFunc() {
  EventLoop loop;
  if (_callback != NULL) {
    _callback(&loop);
  }
  {
    MutexLockGuard lock(_mutex);
    _loop = &loop;
    _cond.broadcast();
  }
  loop.loop();
  _loop = NULL;
}
} // namespace core
} // namespace yarpc
