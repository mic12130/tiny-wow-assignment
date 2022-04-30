#include "message/Messenger.h"

#include <cstdio>

using namespace std;

void Messenger::Send(std::string str) {
  // 000:00 blue dragon 1 born
  int hour = counter / 60;
  int min = counter % 60;

  printf("%03d:%02d %s\n", hour, min, str.c_str());
}

void Messenger::UpdateTime(int counter) {
  Messenger::counter = counter;
}