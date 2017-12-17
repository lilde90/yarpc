// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/socket.h>
#include <yarpc/core/address.h>
#include <yarpc/base/logging.h>
#include <yarpc/base/yarpc_defs.h>
#include <netdb.h>
#include <strings.h>

namespace yarpc {
namespace core {

Address::Address(uint16_t port) {
  bzero(&_addr, sizeof(_addr));
  _addr.sin_family = AF_INET;
  _addr.sin_port = port;
}

Address::Address(std::string ip, uint16_t port) {
  bzero(&_addr, sizeof(_addr));
}

std::string Address::toIp() const {
  char buf[MAX_IP_ADDRESS_BUF_SIZE] = { 0 };
  yarpc::core::toIp(buf, sizeof(buf), getSockAddr());
  return buf;
}

std::string Address::toIpPort() const {
  char buf[MAX_IP_ADDRESS_BUF_SIZE] = { 0 };
  yarpc::core::toIpPort(buf, sizeof(buf), getSockAddr());
  return buf;
}

uint16_t Address::toPort() const {
  return be16toh(_addr.sin_port);
}

uint32_t Address::ipNetEndian() const {
  return _addr.sin_addr.s_addr;
}

bool resolve(std::string ip_address, Address* result) {
  if (result == NULL) {
    return false;
  }
  struct hostent hent;
  struct hostent* he = NULL;
  int herrno = 0;
  bzero(&hent, sizeof(hent));
  char resolve_buff[MAX_RESOLVE_BUF_SIZE] = { 0 };
  int ret = gethostbyname_r(ip_address.c_str(), &hent, resolve_buff, sizeof(resolve_buff), &he, &herrno);
  if (ret == 0 && he != NULL &&
      he->h_addrtype == AF_INET && he->h_length == sizeof(uint32_t)) {
    result->getSockAddrIn().sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
    return true;
  } else {
    if (ret) {
      LOG_ERROR("%s", "resolve address failed");
    }
    return false;
  }
}


} // namespace core
} // namespace yarpc
