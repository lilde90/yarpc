// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_CORE_ACCEPTOR_H_
#define _YARPC_YARPC_CORE_ACCEPTOR_H_

#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <yarpc/core/socket.h>
#include <yarpc/core/address.h>
#include <functional>

namespace yarpc {
namespace core {

class Acceptor {
public:
  typedef std::function<void(int sock_fd, const Address&)>
    NewConnectionCallback;
  Acceptor(EventLoop* loop, const Address listen_addr);
  ~Acceptor();
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
  Socket _accept_socket;
  Channel _accept_channel;
  NewConnectionCallback _newConnectionCallback;
  bool _listening;
};

} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_ACCEPTOR_H_
