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
//__thread pid_t t_current_pid = getpid();
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
} // namespace core
} // namespace yarpc
