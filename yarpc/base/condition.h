// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// wrapper class for condition variable
#ifndef _YARPC_YARPC_BASE_CONDITION_VARIABLE_H_
#define _YARPC_YARPC_BASE_CONDITION_VARIABLE_H_

#include <errno.h>
#include <yarpc/base/mutex_lock.h>

namespace yarpc {
namespace base {

class Condition {
public:
  Condition() {
    pthread_cond_init(&_cond, NULL);
  }

  ~Condition() {
    pthread_cond_destroy(&_cond);
  }

  void wait() {
    pthread_cond_wait(&_cond, &_mutex._lock);
  }

  void wait(unsigned long timeout_in_ms) {
  }

  void signal() {
    pthread_cond_signal(&_cond);
  }

  void broadcast() {
    pthread_cond_broadcast(&_cond);
  }

private:
  MutexLock _mutex;
  pthread_cond_t _cond;

};
} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_CONDITION_VARIABLE_H_
