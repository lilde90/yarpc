// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_TCP_CONNECTION_H_
#define _YARPC_YARPC_CORE_TCP_CONNECTION_H_

#include <yarpc/core/address.h>
#include <yarpc/core/channel.h>
#include <yarpc/core/event_loop.h>
#include <yarpc/core/socket.h>
#include <yarpc/base/yarpc_defs.h>

namespace yarpc {
namespace core {
class TcpConnection {
public:
  TcpConnection(EventLoop* loop,
      const std::string& name,
      int sockfd,
      const Address& local_addr,
      const Address& peer_addr);
  ~TcpConnection();
  EventLoop* getLoop() const {
    return _loop;
  }

  const std::string& name() const {
    return _name;
  }
  
  const Address& localAddr() const {
    return _local_addr;
  }
  
  const Address& peerAddr() const {
    return _peer_addr;
  }

  bool connected() const {
    return _state == Connected;
  }

  bool disconnected() const {
    return _state == Disconnected;
  }

  void send(const void* message, size_t size);
  void send(const std::string& message);

  void startRead();
  void stopRead();
  bool isReading() const {
    return _reading;
  }

  void setConnectionCallback(const ConnectionCallback& cb) {
    _connection_callback = cb;
  }

  void setMessageCallback(const MessageCallback& cb) {
    _message_callback = cb;
  }
private:
  enum TcpConnectionState {
    Disconnected,
    Connecting,
    Connected,
    Disconnecting
  };
  TcpConnectionState _state;
  EventLoop* _loop;
  const std::string _name;
  bool _reading;
  Socket* _socket;
  Channel* _channel;
  const Address _local_addr;
  const Address _peer_addr;
  ConnectionCallback _connection_callback;
  MessageCallback _message_callback;
  
  //
  void handleRead();
  void handleWrite();
  void handleClose();
  void handleError();

  void sendInLoop(const std::string& message);
  void sendInLoop(const void* data, size_t size);

  void startReadInLoop();
  void stopReadInLoop();


  //void setTcpConnectionState(TcpConnectionState s) {
  //  _state = s;
  //}
};
} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_TCP_CONNECTION_H_
