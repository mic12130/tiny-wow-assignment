#pragma once

#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class SpawnPerformer : public TimedEventHandleable {
 public:
  SpawnPerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 != 0) {
      return;
    }

    auto new_red = world_context->red_hq.Spawn();
    auto new_blue = world_context->blue_hq.Spawn();

    if (new_red != nullptr) {
      world_context->red_characters.push_back(new_red);
    }

    if (new_blue != nullptr) {
      world_context->blue_characters.push_back(new_blue);
    }
  }

 private:
  std::shared_ptr<WorldContext> world_context;
};