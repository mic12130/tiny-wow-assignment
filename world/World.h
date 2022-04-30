#pragma once

#include <memory>
#include <vector>

#include "headquarter/Headquarter.h"
#include "world/TimedEventDispatcher.h"
#include "world/WorldContext.h"

class World {
 public:
  World();
  void Run();

 private:
  bool ended_flag = false;
  int location_count = 0;
  std::shared_ptr<WorldContext> world_context;
  std::unique_ptr<Headquarter> red_hq;
  std::unique_ptr<Headquarter> blue_hq;
  std::vector<std::shared_ptr<Character>> red_characters = {};
  std::vector<std::shared_ptr<Character>> blue_characters = {};
  TimedEventDispatcher timed_event_dispatcher;
};