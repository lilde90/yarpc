// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// interface for a bounded blokcing queue

#include <yarpc/base/condition.h>
#include <yarpc/base/mutex_lock.h>
#include <queue>

namespace yarpc {
namespace base {
template <typename T>
class BoundedBlockingQueue {
public:
  explicit BoundedBlockingQueue(int max_size)
  : _mutex(),
    _notEmpty(_mutex),
    _notFull(_mutex),
    _queue(max_size){

  }

  void put(const T& x) {
    MutexLockGuard lock(_mutex);
    while(_queue.full()) {
      _notFull.wait();
    }
    _queue.push_back(x);
    _notEmpty.broadcast();
  }

  T take() {
    MutexLockGuard lock(_mutex);
    while(_queue.empty()) {
      _notEmpty.wait();
    }

    T front(_queue.front());
    _queue.pop_front();
    _notFull.broadcast();
    return front;
  }

  bool empty() const {
    MutexLockGuard lock(_mutex);
    return _queue.empty();
  }

  bool full() const {
    MutexLockGuard lock(_mutex);
    return _queue.full();
  }

  size_t size() const {
    MutexLockGuard lock(_mutex);
    return _queue.size();
  }

  size_t capacity() const {
    MutexLockGuard lock(_mutex);
    return _queue.capacity();
  }
private:
  mutable MutexLock _mutex;
  Condition _notEmpty;
  Condition _notFull;
  std::queue<T> _queue;
};

} // namespace base
} // namespace yarpc
