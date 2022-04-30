#pragma once

#include <memory>
#include <vector>

#include "world/TimedEventHandleable.h"

class TimedEventDispatcher {
 public:
  void AddHandler(std::shared_ptr<TimedEventHandleable> handler);
  void OnTick(int counter);

 private:
  std::vector<std::shared_ptr<TimedEventHandleable>> handlers;
};