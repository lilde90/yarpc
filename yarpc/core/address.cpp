// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/address.h>

namespace yarpc {
namespace core {

Address::Address(uint16_t port) {
}

Address::Address(std::string ip, uint16_t port) {
}

Address::Address(const struct sockaddr_in& addr) {
}

std::string Address::toIp() const {
  return "";
}

std::string Address::toIpPort() const {
  return "";
}

uint16_t Address::toPort() const {
  return 0;
}

uint32_t Address::ipNetEndian() const {
  return 0;
}

bool resolve(std::string ip_address, Address* result) {
  return false;
}


} // namespace core
} // namespace yarpc
