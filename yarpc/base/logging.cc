// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//

#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <yarpc/base/logging.h>

namespace yarpc {
namespace base {

static LogLevel s_log_level = LOG_LEVEL_ERROR;

LogLevel get_log_level() {
  return s_log_level;
}

void set_log_level(LogLevel level) {
  s_log_level = level;
}

void null_log_handler(
    const char *filename, int line,
    LogLevel level, const char* fmt, va_list op) {
}

void default_log_handler(
    const char *filename, int line,
    LogLevel level, const char* fmt, va_list ap ) {
  static const char* level_names[] = { "FATAL", "ERROR", "WARNING", "INFO", "TRACE", "DEBUG"};
  char buf[1024];
  vsnprintf(buf, 1024, fmt, ap);
  struct timeval now_tv;
  gettimeofday(&now_tv, NULL);
  const time_t seconds = now_tv.tv_sec;
  struct tm t;
  localtime_r(&seconds, &t);
  fprintf(stderr, "[yarpc] %s %04d/%02d/%02d-%02d:%02d:%02d.%06d %llx %s:%d] %s\n",
          level_names[level],
          t.tm_year + 1900,
          t.tm_mon + 1,
          t.tm_mday,
          t.tm_hour,
          t.tm_min,
          t.tm_sec,
          static_cast<int>(now_tv.tv_usec),
          static_cast<long long unsigned int>(pthread_self()),
          filename, line, buf);
   fflush(stderr);

   if (level == LOG_LEVEL_FATAL)
   {
       abort();
   }
  
}

static LogHandler* s_log_handler = default_log_handler;

void log_handler(const char* filename, int line,
    LogLevel level, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  s_log_handler(filename, line, level, fmt, ap);
  va_end(ap);
}

LogHandler* set_log_handler(LogHandler* new_handler) {
  LogHandler* old = s_log_handler;
  if (old == &null_log_handler) {
    old = NULL;
  }
  if (new_handler == NULL) {
    s_log_handler = null_log_handler;
  } else {
    s_log_handler = new_handler;
  }
  return old;
}

} // namespace base
} // namespace yarpc

