// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// rwlock wrapper class 

#ifndef _YARPC_YARPC_BASE_RW_LOCK_H_
#define _YARPC_YARPC_BASE_RW_LOCK_H_

#include <pthread.h>

namespace yarpc {
namespace base {

class RWLock {
public:
  RWLock() {
    pthread_rwlock_init(&_lock, NULL);
  }

  ~RWLock() {
    pthread_rwlock_destroy(&_lock);
  }

  void lock() {
    pthread_rwlock_wrlock(&_lock);
  }

  void lock_shared() {
    pthread_rwlock_rdlock(&_lock);
  }

  void unlock() {
    pthread_rwlock_unlock(&_lock);
  }

private:
  pthread_rwlock_t _lock;
};

class ReadLock {
  public:
    ReadLock(RWLock* lock) : _lock(lock) {
      _lock->lock_shared();
    }
    ~ReadLock() {
      _lock->unlock();
    }
  private:
    RWLock* _lock;
};

class WriteLock {
  public:
    WriteLock(RWLock* lock) : _lock(lock) {
      _lock->lock();
    }
    ~WriteLock() {
      _lock->unlock();
    }
  private:
    RWLock* _lock;
};
} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_RW_LOCK_H_
