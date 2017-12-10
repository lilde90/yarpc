// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/socket.h>
#include <yarpc/base/logging.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

namespace yarpc {
namespace core {
const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr) {
  return static_cast<const struct sockaddr*>(static_cast<const void*>(addr));
}

struct sockaddr* sockaddr_cast(struct sockaddr_in* addr) {
  return static_cast<struct sockaddr*>(static_cast<void*>(addr));
}

int connect(int sockfd, const struct sockaddr* addr) {
  return ::connect(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr)));
}
ssize_t read(int sockfd, void *buf, size_t count) {
  return ::read(sockfd, buf, count);
}
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt) {
  return ::readv(sockfd, iov, iovcnt);
}
ssize_t write(int sockfd, const void* buf, size_t count) {
  return ::write(sockfd, buf, count);
}
void close(int sockfd) {
  if (::close(sockfd) < 0) {
    //LOG_ERROR("%s", "close failed");
  }
}
void shutdown(int sockfd) {
  if (::shutdown(sockfd, SHUT_WR) < 0) {
    //LOG_ERROR("%s", "shutdown failed");
  }
}
void bind(int sockfd, const struct sockaddr* addr) {
  int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr)));
  if (ret < 0) {
    //LOG_FATAL("%s", "bind failed");
  }
}
void listen(int sockfd) {
  int ret = ::listen(sockfd, SOMAXCONN);
  if (ret < 0) {
    //LOG_FATAL("%s", "list failed");
  }
}

int create(sa_family_t family) {
  int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
  if (sockfd < 0) {
  }
  return sockfd;
}

int accept(int sockfd, struct sockaddr_in* addr) {
  socklen_t addrlen = static_cast<socklen_t>(sizeof *addr);
  int connfd = ::accept(sockfd, sockaddr_cast(addr), &addrlen);
  int flags = ::fcntl(sockfd, F_GETFL, 0);
  flags |= O_NONBLOCK;
  int ret = ::fcntl(sockfd, F_SETFL, flags);
  flags = ::fcntl(sockfd, F_GETFD, 0);
  flags |= FD_CLOEXEC;
  ret = ::fcntl(sockfd, F_SETFD, flags);
  if (ret < 0 || connfd < 0) {
    //int savedErrno = errno;
  }
  return connfd;
}

} // namespace core
} // namespace yarpc
