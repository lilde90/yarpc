// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/epoller.h>
#include <string.h>

namespace yarpc {
namespace core {

const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

EPoller::EPoller(EventLoop* loop)
  :_owner_loop(loop),
  _fd(epoll_create(_s_init_fd_num)),
  _events(_s_init_events_size) {
  if (_fd < 0) {
  }
}

EPoller::~EPoller() {
  close(_fd);
}

void EPoller::poll(int timeout_ms,
    std::vector<Channel*>* active_channels) {
  int events_num = epoll_wait(_fd,
      &*_events.begin(),
      static_cast<int>(_events.size()),
      timeout_ms);
  // fill active channel
  if (events_num > 0) {
    fillActiveChannels(events_num, active_channels);
    if (static_cast<size_t>(events_num) == _events.size()) {
      _events.resize(events_num * 2);
    }
  } else if (events_num == 0) {
  } else {
  }
}

void EPoller::fillActiveChannels(int events_num, std::vector<Channel*>* active_channels) {

  for (int i = 0; i < events_num; ++i) {
    Channel* channel = static_cast<Channel*>(_events[i].data.ptr);
    channel->set_revents(_events[i].events);
    active_channels->push_back(channel);
  }
}

void EPoller::updateChannel(Channel* channel) {
  int index = channel->index();
  // a new one
  if (index == kNew || index == kDeleted) {
    if (index == kNew) {
      int fd = channel->fd();
      _channels[fd] = channel;
    } else {
    }
    channel->set_index(kAdded);
    update(EPOLL_CTL_ADD, channel);
  } else {
    //int fd = channel->fd();
    if(channel->isNoneEvent()) {
      update(EPOLL_CTL_DEL, channel);
      channel->set_index(kDeleted);
    } else  {
      update(EPOLL_CTL_MOD, channel);
    }
  }
}

void EPoller::removeChannel(Channel* channel) {
  int fd = channel->fd();
  int index = channel->index();
  /*size_t n = */_channels.erase(fd);
  if (index == kAdded) {
    update(EPOLL_CTL_DEL, channel);
  }
  channel->set_index(kNew);
}

void EPoller::update(int op, Channel* channel) {
  struct epoll_event event;
  bzero(&event, sizeof(event));
  event.events = channel->events();
  event.data.ptr = channel;
  int fd = channel->fd();
  if (epoll_ctl(_fd, op, fd, &event) < 0) {
  }
}

bool EPoller::hasChannel(Channel* channel) {
  
  auto it = _channels.find(channel->fd());
  return it != _channels.end() && it->second == channel;
}

} // namespace core
} // namespace yarpc
