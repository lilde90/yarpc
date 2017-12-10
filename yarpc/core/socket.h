// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_CORE_SOCKET_H_
#define _YARPC_YARPC_CORE_SOCKET_H_

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/unistd.h>

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

const struct sockaddr* sockaddr_cast(const struct sockaddr_in*);
struct sockaddr* sockaddr_cast(struct sockaddr_in*);
int connect(int sockfd, const struct sockaddr* addr);
ssize_t read(int sockfd, void *buf, size_t count);
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t write(int sockfd, const void* buf, size_t count);
void close(int sockfd);
void shutdown(int sockfd);
void bind(int sockfd, const struct sockaddr* addr);
void listen(int sockfd);
int create(sa_family_t family);
int accept(int sockfd, struct sockaddr_in* addr);


} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_SOCKET_H_
