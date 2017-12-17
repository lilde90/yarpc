// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
//
#ifndef _YARPC_YARPC_CORE_EPOLLER_H_
#define _YARPC_YARPC_CORE_EPOLLER_H_
#include <yarpc/core/event_loop.h>
#include <yarpc/core/channel.h>
#include <vector>
#include <sys/epoll.h>
#include <unordered_map>
namespace yarpc {
namespace core {
class EventLoop;
class Channel;

class EPoller {
public:
  EPoller(EventLoop* loop);
  ~EPoller();
  void updateChannel(Channel* channel);
  void removeChannel(Channel* channel);
  void update(int op, Channel* channel);
  void poll(int timeout_ms, std::vector<Channel*>* active_channels);
private:
  void fillActiveChannels(int event_num, std::vector<Channel*>* active_channels);
private:
  static const int _s_init_fd_num = 1024;
  static const int _s_init_events_size = 16;
  EventLoop* _owner_loop;
  int _fd;
  std::vector<struct epoll_event> _events;
  std::unordered_map<int, Channel*> _channels;

};
} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_EPOLLER_H_
