// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// interface for mutex lock wrapper
//
#ifndef _YARPC_BASE_MUTEX_LOCK_H_
#define _YARPC_BASE_MUTEX_LOCK_H_

#include <pthread.h>

namespace yarpc {
namespace base {
class MutexLock {
public:
  MutexLock() {
    pthread_mutex_init(&lock, NULL);
  }

  ~MutexLock() {
    pthread_mutex_destroy(&_lock);
  }

  void lock() {
    pthread_mutex_lock(&_lock);
  }

  void unlock() {
    pthred_mutex_unlock(&_lock);
  }
private:
  pthread_mutex_t _lock;
}
} // namespace base
} // namespace yarpc

#endif // _YARPC_BASE_MUTEX_LOCK_H_
