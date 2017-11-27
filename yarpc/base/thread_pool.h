// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_BASE_THREAD_H_
#define _YARPC_YARPC_BASE_THREAD_H_

#include <vector>
#include <yarpc/base/condition.h>
#include <yarpc/base/thread.h>
#include <yarpc/base/mutex_lock.h>
#include <deque>
#include <functional>

namespace yarpc {
namespace base {

class ThreadPool {
public:
  typedef yarpc::base::Thread::ThreadFunc TaskFunc;
  //typedef void *(*yarpc::base::Thread::ThreadFunc)(void);
  ThreadPool(const std::string& name);
  ~ThreadPool();

  void setMaxQueueSize(int size) { _max_queue_size = size; }
  void setThreadInitFunc(TaskFunc task) {
    _threadInitFunc = task;
  }

  void start(int thread_num);
  void stop();
  void run(const TaskFunc& task);

  inline const std::string& name() {
    return _name;
  }

  size_t taskQueueSize() const;

private:
  bool isFull() const;
  TaskFunc take();
  void threadRunFunc();

  mutable MutexLock _mutex;
  std::string _name;
  Condition _not_empty;
  Condition _not_full;
  TaskFunc _threadInitFunc;
  std::vector<yarpc::base::Thread*> _threads;
  std::deque<TaskFunc> _task_queue;
  size_t _max_queue_size;
  bool _running;
};

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_THREAD_H_
