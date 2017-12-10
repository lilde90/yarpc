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
  yarpc::base::set_log_level(LOG_LEVEL_##level)

#define LOG(level, fmt, arg...) \
  yarpc::base::log_handler(__FILE__, __LINE__, yarpc::base::LOG_LEVEL_##level, fmt, ##arg) \

#define LOG_FATAL(fmt, arg...) \
  LOG(FATAL, fmt, arg);
#define LOG_ERROR(fmt, arg...) \
  LOG(ERROR, fmt, arg);
#define LOG_WARNING(fmt, arg...) \
  LOG(WARNING, fmt, arg);
#define LOG_NOTICE(fmt, arg...) \
  LOG(NOTICE, fmt, arg);
#define LOG_INFO(fmt, arg...) \
  LOG(INFO, fmt, arg);
#define LOG_TRACE(fmt, arg...) \
  LOG(INFO, fmt, arg);
#define LOG_DEBUG(fmt, arg...) \
  LOG(DEBUG, fmt, arg);

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_LOGGING_H_
