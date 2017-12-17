// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_EVENTLOOPTHREADPOOL_H_
#define _YARPC_YARPC_CORE_EVENTLOOPTHREADPOOL_H_

#include <vector>
#include <string>

namespace yarpc {
namespace core {

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool {
public:
  typedef std::function<void(EventLoop*)> ThreadInitCallback;
  EventLoopThreadPool(EventLoop* base_loop, const std::string& name);
  
  ~EventLoopThreadPool();

  void setThreadNum(int num) {
    _thread_num = num;
  }

  void start(const ThreadInitCallback& cb);

  EventLoop* getNextLoop();
  EventLoop* getHashLoop(size_t hash_code);

  std::vector<EventLoop*> getAllLoops();

  bool isStarted() const {
    return _started;
  }

  const std::string& name() const {
    return _name;
  }

private:
  EventLoop* _base_loop;
  std::string _name;
  bool _started;
  int _thread_num;
  int _next;
  std::vector<EventLoopThread*> _threads;
  std::vector<EventLoop*> _loops;
};

} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_EVENTLOOPTHREADPOOL_H_
