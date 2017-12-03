// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/event_loop.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <pthread.h>
#include <yarpc/base/logging.h>

namespace yarpc {
namespace core {
using namespace yarpc::base;

__thread EventLoop* t_thisThreadLoop = NULL;
EventLoop::EventLoop()
  :_looping(false) {

  _thread_id = static_cast<pid_t>(::syscall(SYS_gettid));
  LOG_TRACE("EventLoop created in thread %d", _thread_id);
  if (t_thisThreadLoop == NULL) {
    t_thisThreadLoop = this;
  } else {
    LOG_FATAL("A EventLoop has been created in thread %d", _thread_id);
  }
  
}

EventLoop::~EventLoop() {
  if (_looping) {
    t_thisThreadLoop = NULL;
  }
}

EventLoop* EventLoop::getEventLoop() {
  return t_thisThreadLoop;
}

void EventLoop::loop() {
  if (_looping) {
    LOG_FATAL("event loop is thread %d is looping", _thread_id);
  }
  _looping = true;
  _looping = false;
}
} // namespace core
} // namespace yarpc
