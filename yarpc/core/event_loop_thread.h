// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_EVENTLOOPTHREAD_H_
#define _YARPC_YARPC_CORE_EVENTLOOPTHREAD_H_

#include <yarpc/base/condition.h>
#include <yarpc/base/mutex_lock.h>
#include <yarpc/base/thread.h>

using namespace yarpc::base;

namespace yarpc {
namespace core {

class EventLoop;

class EventLoopThread {
public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;
  EventLoopThread(const ThreadInitCallback& cb, std::string& name);
  ~EventLoopThread();
  EventLoop* startLoop();

private:
  void threadFunc();
  EventLoop* _loop;
  bool _exiting;
  Thread _thread;
  MutexLock _mutex;
  Condition _cond;
  ThreadInitCallback _callback;
};

} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_EVENTLOOPTHREAD_H_
