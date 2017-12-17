// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_CORE_CONNECTOR_H_
#define _YARPC_YARPC_CORE_CONNECTOR_H_
#include <yarpc/core/address.h>
#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <functional>
namespace yarpc {
namespace core {

class Connector {
public:
  typedef std::function<void(int sockfd)> NewConnectionCallback;
  Connector(EventLoop* loop, const Address& addr);
  ~Connector();

  void setNewConnectionCallback(const NewConnectionCallback& cb) {
    _new_connection_callback = cb;
  }
  void start();
  void restart();
  void stop();
  const Address& serverAddress() const {
    return _server_address;
  }
private:
  enum ConnectState {
    Disconnected,
    Connecting,
    Connected
  };

  void setState(ConnectState s) {
    _state = s;
  }

  void connect();
  void connecting(int sockfd);
  void handleWrite();
  void handleError();
  void retry(int sockfd);
  int removeChannel();
  void resetChannel();

  void startInLoop();
  void stopInLoop();

  EventLoop* _loop;
  Address _server_address;
  bool _connect;
  ConnectState _state;
  Channel* _channel;
  NewConnectionCallback _new_connection_callback;

};
} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_CONNECTOR_H_
