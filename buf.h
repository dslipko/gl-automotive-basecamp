#include <iostream>

class PrintfBuf {
 public:
  PrintfBuf() {
    _buf_size = BUFFER;
    _m_buf = (char*)malloc((_buf_size) * sizeof(char));
    _m_size = 0;
  };
  ~PrintfBuf(){

  };

  void PrintOut();
  void SetBuf(const char* buf);
  void Clearbuf();
  const int BUFFER = 5000000;

 private:
  char* _m_buf = nullptr;
  int _m_size;
  int _buf_size;
  void ReallocateBuf();
};