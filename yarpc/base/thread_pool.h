// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_BASE_THREAD_H_
#define _YARPC_YARPC_BASE_THREAD_H_

#include <vector>
#include <yarpc/base/condition.h>
#include <yarpc/base/thread.h>
#include <yarpc/base/mutex.h>
#include <deque>

namespace yarpc {
namespace base {

class ThreadPoll {
public:
  typedef void *(*TaskFunc)(void);
  ThreadPool(const std::string& name);
  ~ThreadPool();

  void setMaxQueueSize(int size) { _max_queue_size = size; }

  void start(int thread_num);
  void stop();

  inline const std::string& name() {
    return _name;
  }

  inline size_t queueSize() const;

private:
  mutable MutexLock _mutex;
  void run();

  std::string _name;
  Condition _not_empty;
  Condition _not_full;
  std::vector<yarpc::base::Thread*> _threads;
  size_t _max_queue_size;
  bool _running;
};

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_THREAD_H_
