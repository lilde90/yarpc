// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_BASE_THREAD_H_ 
#define _YARPC_BASE_THREAD_H_

#include <yarpc/base/mutex_lock.h>
#include <yarpc/base/rw_lock.h>
#include <yarpc/base/scoped_lock.h>
#include <yarpc/base/condition.h>
#include <yarpc/base/blocking_queue.h>
#include <yarpc/base/bounded_blocking_queue.h>
#include <yarpc/base/logging.h>
#include <yarpc/base/thread_local.h>
#include <string>
#include <pthread.h>
#include <functional>

namespace yarpc {
namespace base {

class Thread {
public:
  typedef std::function<void()> ThreadFunc;
  explicit Thread(const ThreadFunc& func, const std::string& name = std::string());
  ~Thread();

  void start();
  int join();

  inline bool started() const { return _started; }
  inline const std::string& name() const { return _name;}

private:
  bool _started;
  bool _joined;
  ThreadFunc _func;
  pthread_t _pthread_id;
  std::string _name;
};

struct ThreadData {
  typedef yarpc::base::Thread::ThreadFunc ThreadFunc;
public:
  ThreadData(const ThreadFunc& func,
      const std::string& name) :
    _func(func),
    _name(name) {}
  void run() {
    _func();
  }
private:
  ThreadFunc _func;
  std::string _name;
};

void* threadStartFunc(void* obj) {
  ThreadData* data = static_cast<ThreadData*>(obj);
  data->run();
  delete data;
  return NULL;
}

} // namespace base
} // namespace yarpc

#endif // _YACRPC_BASE_THREAD_H_
