// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_CORE_ACCEPTOR_H_
#define _YARPC_YARPC_CORE_ACCEPTOR_H_

#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <functional>

namespace yarpc {
namespace core {

class Acceptor {
public:
  typedef std::function<void(int sock_fd/*, const InetAddress&*/)>
    NewConnectionCallback;
  Acceptor(EventLoop* loop/*, const InetAddress listen_addr*/);
  void setNewConnectionCallback(const NewConnectionCallback& cb) {
    _newConnectionCallback = cb;
  }
  bool listening() const {
    return _listening;
  }
  void listen();
private:
  void handleRead();

private:
  EventLoop* _loop;
  Channel _accept_channel;
  NewConnectionCallback _newConnectionCallback;
  bool _listening;
};

} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_ACCEPTOR_H_
