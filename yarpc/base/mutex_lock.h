// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// interface for mutex lock wrapper
//
#ifndef _YARPC_BASE_MUTEX_LOCK_H_
#define _YARPC_BASE_MUTEX_LOCK_H_

#include <pthread.h>

namespace yarpc {
namespace base {

class Condition;

class MutexLock {
public:
  MutexLock() {
    pthread_mutex_init(&_lock, NULL);
  }

  ~MutexLock() {
    pthread_mutex_destroy(&_lock);
  }

  void lock() {
    pthread_mutex_lock(&_lock);
  }

  void unlock() {
    pthread_mutex_unlock(&_lock);
  }
  pthread_mutex_t getMutex() {
    return _lock;
  }
private:
  friend class Condition;
  pthread_mutex_t _lock;
};

class MutexLockGuard {
  public:
    MutexLockGuard(MutexLock& mutex) : _mutex(mutex) {
      _mutex.lock();
    }

    ~MutexLockGuard() {
      _mutex.unlock();
    }
  private:
    MutexLock& _mutex;

};

} // namespace base
} // namespace yarpc

#endif // _YARPC_BASE_MUTEX_LOCK_H_
