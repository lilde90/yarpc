// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
//
#include <yarpc/base/thread.h>

namespace yarpc {
namespace base {

Thread::Thread(const ThreadFunc& func,
    const std::string& name) :
  _started(false),
  _joined(false),
  _func(func),
  _pthread_id(0),
  _name(name) {
}

Thread::~Thread() {
  if (_started && !_joined) {
    pthread_detach(_pthread_id);
  }
}

void Thread::start() {
  if (_started) {
    return;
  }
  
  _started = true;
  ThreadData* data = new ThreadData(_func, _name);
  if (pthread_create(&_pthread_id, NULL, &threadStartFunc, data) != 0) {
    _started = false;
    LOG_FATAL("%s", "pthread_create failed");
  } else {
  }
}

int Thread::join() {
  if (!_started) {
    LOG_FATAL("thread[%d] has not started", _pthread_id);
  }

  if (_joined) {
    LOG_FATAL("thread[%d] has been joined", _pthread_id);
  }

  _joined = true;
  return pthread_join(_pthread_id, NULL);
}


} // namespace base
} // namespace yarpc
