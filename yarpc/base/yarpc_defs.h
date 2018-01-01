// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_CORE_YARPC_DEFS_H_
#define _YARPC_YARPC_CORE_YARPC_DEFS_H_
#include <functional>
namespace yarpc {
namespace core {
class TcpConnection;

static const int MAX_IP_ADDRESS_BUF_SIZE = 128;
static const int MAX_RESOLVE_BUF_SIZE = 64 * 1024;

typedef std::function<void(const TcpConnection*)> ConnectionCallback;
typedef std::function<void(const TcpConnection*,
    const void* message,
    int size)> MessageCallback;

} // namespace core
} // namespace yarpc
#endif // _YARPC_YARPC_CORE_YARPC_DEFS_H_
