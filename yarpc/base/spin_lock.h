// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_BASE_SPIN_LOCK_H_
#define _YARPC_YARPC_BASE_SPIN_LOCK_H_

#include <pthread.h>

namespace yarpc {
namespace base {

class SpinLock {
public:
  SpinLock() {
    pthread_spin_init(&_lock, NULL);
  }

  ~SpinLock() {
    pthread_spin_destroy(&_lock);
  }

  void lock() {
    pthread_spin_lock(&_lock);
  }

  bool try_lock() {
    return pthread_spin_trylock(&_lock) == 0;
  }
  
  void unlock() {
    pthread_spin_unlock(&_lock);
  }
private:
  pthread_spinlock_t _lock
};

} // namespace base
} // namespace yarpc
