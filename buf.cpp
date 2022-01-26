#include "buf.h"

#include <cstring>

void PrintfBuf::PrintOut() {
  printf("%s \n", _m_buf);
  PrintfBuf::Clearbuf();
}

void PrintfBuf::SetBuf(const char* buf) {
  if ((sizeof(buf) + _m_size) >= _buf_size) {
    PrintfBuf::ReallocateBuf();
  }
  for (int i = _m_size; i <= _m_size + sizeof(buf + 1); i++) {
    _m_buf[i] = buf[i - _m_size];
  }
  _m_size += sizeof(buf) + 1;
}

void PrintfBuf::ReallocateBuf() {
  char* temp_buf;
  _buf_size = _buf_size + BUFFER;
  temp_buf = (char*)malloc((_buf_size) * sizeof(char));
  std::copy(_m_buf, _m_buf + _m_size, temp_buf);
  _m_buf = (char*)malloc((_buf_size) * sizeof(char));
  _m_buf = temp_buf;
}

void PrintfBuf::Clearbuf() {
  _m_size = 0;
  _buf_size = BUFFER;
}
