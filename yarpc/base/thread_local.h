// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_BASE_THREAD_LOCAL_H_
#define _YARPC_YARPC_BASE_THREAD_LOCAL_H_

#include <pthread.h>

namespace yarpc {
namespace base {

template<typename T>
class ThreadLocal {
public:
  ThreadLocal() {
    pthread_key_create(&_pkey, &ThreadLocal::destructor);
  }

  ~ThreadLocal() {
    pthread_key_delete(_pkey);
  }

  T& value() {
    T* thread_value = static_cast<T*>(pthread_getspecific(_pkey));
    if (thread_value == NULL) {
      T* obj = new T();
      pthread_setsetspecific(_pkey, obj);
      thread_value = obj;
    }
    return *thread_value;
  }
private:
  pthread_key_t _pkey;
private:
  static void destructor(void* x) {
    T* obj = static_cast<T*>(x);
    delete obj;
  }
};

} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_THREAD_LOCAL_H_
