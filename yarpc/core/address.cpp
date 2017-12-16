// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/socket.h>
#include <yarpc/core/address.h>
#include <yarpc/base/logging.h>
#include <yarpc/base/yarpc_defs.h>
#include <strings.h>

namespace yarpc {
namespace core {

Address::Address(uint16_t port) {
  bzero(&_addr, sizeof(_addr));
  _addr.sin_family = AF_INET;
  //in_addr_t ip = 
  _addr.sin_port = port;
}

Address::Address(std::string ip, uint16_t port) {
  bzero(&_addr, sizeof(_addr));
}

std::string Address::toIp() const {
  char buf[MAX_IP_ADDRESS_BUF_SIZE] = { 0 };
  return buf;
}

std::string Address::toIpPort() const {
  char buf[MAX_IP_ADDRESS_BUF_SIZE] = { 0 };
  return buf;
}

uint16_t Address::toPort() const {
  return 0;
}

uint32_t Address::ipNetEndian() const {
  return _addr.sin_addr.s_addr;
}

bool resolve(std::string ip_address, Address* result) {
  return false;
}


} // namespace core
} // namespace yarpc
