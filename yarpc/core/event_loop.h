// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_H_
#define _YARPC_YARPC_CORE_H_

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>

namespace yarpc {
namespace core {
class EventLoop {

public:
  EventLoop();

  ~EventLoop();
  void loop();
  bool isInLoopThread() const;
  static EventLoop* getEventLoop();
private:
  bool _looping;
  pid_t _thread_id;
};
} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_H_
