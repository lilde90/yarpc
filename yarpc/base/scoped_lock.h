// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// wrapper class for scoped lock

#ifndef _YARPC_YARPC_SCOPED_LOCK_H_
#define _YARPC_YARPC_SCOPED_LOCK_H_
namespace yarpc {
namespace base {

template <typename Type>
class ScopedLock {
public:
  ScopedLock (Type& lock) : _lock(lock) {
    _lock->lock();
  }

  ScopedLock (Type* lock) : _lock(lock) {
    _lock->lock();
  }

  ~ScopedLock() {
    _lock->unlock();
  }

private:
  Type* _lock;
};

} // namespace base
} // namespace yarpc
#endif // _YARPC_YARPC_SCOPED_LOCK_H_
