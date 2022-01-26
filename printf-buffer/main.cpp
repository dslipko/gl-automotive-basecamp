#include <chrono>
#include <iostream>

#include "buf.h"

int main(int, char**) {
  PrintfBuf printfbuf;
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 90000; i++) {
    printfbuf.SetBuf("qwertyuio");
  }

  printfbuf.PrintOut();
  auto end = std::chrono::system_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

  std::cout << std::endl;
  auto start2 = std::chrono::system_clock::now();
  for (int i = 0; i < 90000; i++) {
    std::cout << "zxcvbnmlk";
  }

  auto end2 = std::chrono::system_clock::now();
  auto elapsed2 =
      std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
  std::cout << std::endl
            << "Time PrinfBuf:" << elapsed.count() << "ms" << std::endl;
  std::cout << "Time std::cout :" << elapsed2.count() << "ms" << std::endl;
}
