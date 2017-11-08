// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
// interface and implementation of blocking queue

#ifndef _YARPC_YARPC_BASE_BLOCKING_QUEUE_H_
#define _YARPC_YARPC_BASE_BLOCKING_QUEUE_H_

#include <yarpc/base/condition.h>
#include <yarpc/base/mutex_lock.h>

#include <deque>
#include <assert.h>

namespace yarpc {
namespace base {

template<typename T>
class BlockingQueue {
public:
  BlockingQueue() : _mutex(), _notEmpty(_mutex), _queue() {
  }

  void put(const T& x) {
    MutexLockGuard lock(_mutex);
    _queue.push_back(x);
    _notEmpty.signal();
  }

  T take() {
    MutexLockGuard lock(_mutex);
    while(_queue.empty()) {
      _notEmpty.wait();
    }
    T front(_queue.front());
    _queue.pop_front();
    return front;
  }
  
  size_t size() const {
    MutexLockGuard lock(_mutex);
    return _queue.size();
  }

private:
  mutable MutexLock _mutex;
  Condition _notEmpty;
  std::deque<T> _queue;

};

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_BLOCKING_QUEUE_H_;
