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
#include <sys/uio.h>
#include <unistd.h>
#include <linux/unistd.h>

namespace yarpc {
namespace core {

class Address;
class Socket {
public:
  Socket(int fd) :
    _fd(fd) {
  }
  ~Socket();
  int fd() const {
    return _fd;
  }
  
  void bind(const Address& local_addr);
  void listen();

  int accept(Address* peer_addr);
  
  void shutdown();

  void setTcpNoDelay(bool open);
  void setReuseAddr(bool open);
  void setReusePort(bool open);
  void setKeepAlive(bool open);
private:
  const int _fd;
};

const struct sockaddr* sockaddr_cast(const struct sockaddr_in*);
struct sockaddr* sockaddr_cast(struct sockaddr_in*);
const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr*);

int connect(int sockfd, const struct sockaddr* addr);
void close(int sockfd);
void shutdown(int sockfd);
void bind(int sockfd, const struct sockaddr* addr);
void listen(int sockfd);
int create(sa_family_t family);
int accept(int sockfd, struct sockaddr_in* addr);

ssize_t read(int sockfd, void *buf, size_t count);
ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
ssize_t write(int sockfd, const void* buf, size_t count);

struct sockaddr_in getLocalAddr(int sockfd);
struct sockaddr_in getPeerAddr(int sockfd);

void toIp(char* buf, size_t size, const struct sockaddr* addr);
void toIpPort(char* buf, size_t size, const struct sockaddr* addr);
void fromIpPort(const char* ip, uint16_t port,
    struct sockaddr_in* addr);

} // namespace core
} // namespace yarpc

#endif // _YARPC_YARPC_CORE_SOCKET_H_
