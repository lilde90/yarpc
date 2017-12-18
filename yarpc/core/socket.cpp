// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/socket.h>
#include <yarpc/base/logging.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <yarpc/core/address.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

namespace yarpc {
namespace core {

Socket::~Socket() {
  yarpc::core::close(_fd);
}

void Socket::bind(const Address& local_addr) {
  yarpc::core::bind(_fd, local_addr.getSockAddr());
}

void Socket::listen() {
  yarpc::core::listen(_fd);
}

int Socket::accept(Address& peer_addr) {
  struct sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  int connfd = yarpc::core::accept(_fd, &addr);
  if (connfd >= 0) {
    peer_addr.setSockAddr(addr);
  }
  return connfd;
}

void Socket::shutdown() {
  yarpc::core::shutdown(_fd);
}

void Socket::setTcpNoDelay(bool open) {
  int val = open ? 1 : 0;
  int ret = setsockopt(_fd, IPPROTO_TCP, TCP_NODELAY,
      &val, static_cast<socklen_t>(sizeof(val)));
  if (ret < 0 && open) {
    LOG_ERROR("%s", "set tcp no delay failed");
  }
}

void Socket::setReuseAddr(bool open) {
  int val = open ? 1 : 0;
  int ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR,
      &val, static_cast<socklen_t>(sizeof(val)));
  if (ret < 0 && open) {
    LOG_ERROR("%s", "set reuse addr failed");
  }
}

void Socket::setReusePort(bool open) {
  int val = open ? 1 : 0;
  int ret = setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR,
      &val, static_cast<socklen_t>(sizeof(val)));
  if (ret < 0 && open) {
    LOG_ERROR("%s", "set reuse port failed");
  }
}

void Socket::setKeepAlive(bool open) {
  int val = open ? 1 : 0;
  int ret = setsockopt(_fd, SOL_SOCKET, SO_KEEPALIVE,
      &val, static_cast<socklen_t>(sizeof(val)));
  if (ret < 0 && open) {
    LOG_ERROR("%s", "set keep alive failed");
  }
}

const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr) {
  return static_cast<const struct sockaddr*>(static_cast<const void*>(addr));
}

struct sockaddr* sockaddr_cast(struct sockaddr_in* addr) {
  return static_cast<struct sockaddr*>(static_cast<void*>(addr));
}

const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr) {
  return static_cast<const struct sockaddr_in*>(static_cast<const void*>(addr));
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
    LOG_ERROR("close fd:%d failed", sockfd);
  }
}
void shutdown(int sockfd) {
  if (::shutdown(sockfd, SHUT_WR) < 0) {
    LOG_ERROR("shutdown fd:%d failed", sockfd);
  }
}
void bind(int sockfd, const struct sockaddr* addr) {
  int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof(struct sockaddr)));
  if (ret < 0) {
    LOG_FATAL("bind fd:%d failed", sockfd);
  }
}
void listen(int sockfd) {
  int ret = ::listen(sockfd, SOMAXCONN);
  if (ret < 0) {
    LOG_FATAL("listen fd:%d failed", sockfd);
  }
}

int create(sa_family_t family) {
  int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
  if (sockfd < 0) {
    //LOG_FATAL("create socket failed");
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
    int savedErrno = errno;
    LOG_FATAL("fd %d accept error %d", connfd, savedErrno);
  }
  return connfd;
}

struct sockaddr_in getLocalAddr(int sockfd) {
  struct sockaddr_in local_addr;
  bzero(&local_addr, sizeof(local_addr));
  socklen_t addr_len = static_cast<socklen_t>(sizeof(local_addr));
  if (getsockname(sockfd, sockaddr_cast(&local_addr), &addr_len) < 0) {
    LOG_ERROR("%s", "getLocalAddr failed");
  }
  return local_addr;
}

struct sockaddr_in getPeerAddr(int sockfd) {
  struct sockaddr_in peer_addr;
  bzero(&peer_addr, sizeof(peer_addr));
  socklen_t peer_len = static_cast<socklen_t>(sizeof(peer_addr));
  if (getpeername(sockfd, sockaddr_cast(&peer_addr), &peer_len) < 0) {
    LOG_ERROR("%s", "getPeerAddr failed");
  }
  return peer_addr;
}

void toIp(char* buf, size_t size, const struct sockaddr* addr) {
  if (addr->sa_family == AF_INET) {
    const struct sockaddr_in* addr_in = sockaddr_in_cast(addr);
    inet_ntop(AF_INET, &addr_in, buf, static_cast<socklen_t>(size));
  }
}

void toIpPort(char* buf, size_t size, const struct sockaddr* addr) {
  toIp(buf, size, addr);
  size_t end = strlen(buf);
  const struct sockaddr_in* addr_in = sockaddr_in_cast(addr);
  uint16_t port = be16toh(addr_in->sin_port);
  snprintf(buf + end, size - end, ":%u", port);
}

void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr) {
  addr->sin_family = AF_INET;
  addr->sin_port = be16toh(port);
  if (inet_pton(AF_INET, ip, &addr->sin_addr) < 0) {
    LOG_ERROR("%s", "fromIpPort failed");
  }

}

} // namespace core
} // namespace yarpc
