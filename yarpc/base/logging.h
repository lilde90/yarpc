// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#ifndef _YARPC_YARPC_BASE_LOGGING_H_
#define _YARPC_YARPC_BASE_LOGGING_H_
#include <stdarg.h>

namespace yarpc {
namespace base {

enum LogLevel {
    LOG_LEVEL_FATAL   = 0,
    LOG_LEVEL_ERROR   = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_NOTICE  = 3,
    LOG_LEVEL_INFO    = 3,
    LOG_LEVEL_TRACE   = 4,
    LOG_LEVEL_DEBUG   = 5,
};

typedef void LogHandler(const char* filename, int line, LogLevel level, const char* fmt, va_list ap);

LogHandler* set_log_handler(LogHandler* new_handle);

LogLevel get_log_level();

void set_log_level(LogLevel level);

void log_handler(const char* filename, int line, LogLevel level, const char* fmt, ...);

#define YARPC_SET_LOG_LEVEL(level) \
  set_log_level(LOG_LEVEL_##level)

#define LOG(level, fmt, arg...) \
  log_handler(\
      __FILE__, __LINE__, LOG_LEVEL_##level, fmt, ##arg) \

#define LOG_FATAL(fmt, arg...) \
  LOG(FATAL, fmt, arg);

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_LOGGING_H_
