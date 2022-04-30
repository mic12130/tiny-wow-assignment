#pragma once

#include <string>

class Messenger {
 public:
  static void Send(std::string str);
  static void UpdateTime(int counter);

 private:
  inline static int counter = 0;
};