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
    struct timespec ts;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long usec = tv.tv_usec + timeout_in_ms * 1000;
    ts->tv_sec = tv.tv_sec + usec / 1000000;
    ts->tv_nsec = (usec % 1000000) * 1000;
    int error = pthread_cond_timedwait(&_cond, &mutex._lock, &ts);
    if (error == 0) {
      return true;
    } else if (error == ETIMEDOUT) {
      return false;
    } else {
      return false;
    }
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
