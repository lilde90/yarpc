// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#include <yarpc/core/tcp_client.h>
namespace yarpc {
namespace core {
TcpClient::TcpClient(EventLoop* loop,
    const Address& serverAddr,
    const std::string& name) {
}
TcpClient::~TcpClient() {
}

void TcpClient::connect() {
}

void TcpClient::disconnect() {
}

void TcpClient::stop() {
}
} // namespace core
} // namespace yarpc
