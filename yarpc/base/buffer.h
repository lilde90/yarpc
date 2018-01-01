// Copyright 2017 lilde90. All Rights Reserved.
// Author: Pan Li (panli.me@gmail.com)
//
#ifndef _YARPC_YARPC_BASE_BUFFER_H_
#define _YARPC_YARPC_BASE_BUFFER_H_

#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

namespace yarpc {
namespace base {
class Buffer {
public:
  static const size_t S_INIT_SIZE = 1024;
  Buffer(size_t init_size = S_INIT_SIZE):
    _buffer(init_size),
    _read_index(0),
    _write_index(0) {
  }

  void swap(Buffer& rhs) {
    _buffer.swap(rhs._buffer);
    std::swap(_read_index, rhs._read_index);
    std::swap(_write_index, rhs._write_index);
  }

  size_t readableSize() const {
    return _write_index - _read_index;
  }

  size_t writeableSize() const {
    return _buffer.size() - _write_index;
  }

  const char* peek() const {
    return begin() + _read_index;
  }

  void read(size_t len) {
    if (len < readableSize()) {
      _read_index += len;
    } else {
      
      // buffer is empty;
      _read_index = 0;
      _write_index = 0;
    }
  }

  void readAll() {
    _read_index = 0;
    _write_index = 0;
  }

  //void readInt64() {
  //  read(sizeof(int64_t));
  //}
  //void readInt32() {
  //  read(sizeof(int32_t));
  //}
  //void readInt16() {
  //  read(sizeof(int16_t));
  //}
  //void readInt8() {
  //  read(sizeof(int8_t));
  //}

  std::string readAllAsString() {
    return readAsString(readableSize());
  }

  std::string readAsString(size_t len) {
    std::string result(peek(), len);
    read(len);
    return result;
  }

  void write(std::string& str) {
    write(str.data(), str.size());
  }

  void write(const char* data, size_t len) {
    if (writeableSize() < len) {
      // make space;
    }
    std::copy(data, data+len, begin() + _write_index);
    _write_index += len;
  }

  void write(const void* data, size_t len) {
    write(static_cast<const char*>(data), len);
  }

private:
  char * begin() {
    return &*_buffer.begin();
  }
  
  const char* begin() const {
    return &*_buffer.begin();
  }
  std::vector<char> _buffer;
  size_t _read_index;
  size_t _write_index;

};


} // namespace base
} // namespace yarpc

#endif // _YARPC_YARPC_BASE_BUFFER_H_
