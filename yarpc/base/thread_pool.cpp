// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#include <yarpc/base/thread_pool.h>
#include <yarpc/base/logging.h>
#include <stdio.h>

namespace yarpc {
namespace base {

ThreadPool::ThreadPool(const std::string& name) :
  _mutex(),
  _name(name),
  _not_empty(),
  _not_full(),
  _max_queue_size(0),
  _running(false) {
};

ThreadPool::~ThreadPool() {
  if (_running) {
    stop();
  }
}

void ThreadPool::start(int thread_num) {
  if (_threads.size() == 0) {
    LOG_FATAL("%s", "thread group size is 0");
  }
  _running = true;
  for (int i = 0; i < thread_num; ++i) {
    char id[32];
    snprintf(id , sizeof(id), "%d", i+1);
    _threads.push_back(
        new yarpc::base::Thread(std::bind(&ThreadPool::threadRunFunc, this), _name+id));
    _threads[i]->start();
  }

  if (thread_num == 0 && _threadInitFunc != NULL) {
    _threadInitFunc();
  }

}

void ThreadPool::stop() {
  {
    MutexLockGuard lock(_mutex);
    _running = false;
    _not_empty.broadcast();
  }

  for (size_t i = 0; i < _threads.size(); ++i) {
    _threads[i]->join();
  }

  for (size_t i = 0; i < _threads.size(); ++i) {
    delete _threads[i];
  }
}

size_t ThreadPool::taskQueueSize() const {
  MutexLockGuard lock(_mutex);
  return _task_queue.size();
}

void ThreadPool::run(const TaskFunc& task) {
  if (_threads.empty()) {
    task();
  } else {
    MutexLockGuard lock(_mutex);
    while(isFull()) {
      _not_full.wait();
    }
    _task_queue.push_back(task);
    _not_empty.broadcast();
  }
}

ThreadPool::TaskFunc ThreadPool::take() {
  MutexLockGuard lock(_mutex);
  while(_task_queue.empty() && _running) {
    _not_empty.wait();
  }
  TaskFunc task;
  if (!_task_queue.empty()) {
    task = _task_queue.front();
    _task_queue.pop_front();
    if (_max_queue_size > 0) {
      _not_full.broadcast();
    }
  }
  return task;
}

bool ThreadPool::isFull() const {
  return _max_queue_size > 0 && _task_queue.size() >= _max_queue_size;
}

void ThreadPool::threadRunFunc() {
  if (_threadInitFunc) {
    _threadInitFunc();
  }
  while(_running) {
    TaskFunc task(take());
    if (task) {
      task();
    }
  }
}

} // namespace base
} // namespace yarpc

