// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_SOCKET_H_
#define _YARPC_YARPC_CORE_SOCKET_H_


namespace yarpc {
namespace core {
class Socket {
public:
  Socket(int fd) :
    _fd(fd) {
  }
private:
  const int _fd;
};

} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_SOCKET_H_
