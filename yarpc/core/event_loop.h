// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_EVENT_LOOP_H_
#define _YARPC_YARPC_CORE_EVENT_LOOP_H_

#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <yarpc/core/channel.h>
#include <yarpc/core/epoller.h>
#include <vector>

namespace yarpc {
namespace core {

class Channel;
class EPoller;

class EventLoop {
public:
  EventLoop();

  ~EventLoop();
  void loop();
  bool isInLoopThread() const;
  static EventLoop* getEventLoop();

  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);
  bool hasChannel(Channel* channel);
private:
  bool _looping;
  bool _quit;
  EPoller* _epoller;
  std::vector<Channel*> _active_channel;
  pid_t _thread_id;

};
} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_EVENT_LOOP_H_
