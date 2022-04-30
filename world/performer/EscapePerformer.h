#pragma once

#include "message/Messenger.h"
#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class EscapePerformer : public TimedEventHandleable {
 public:
  EscapePerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 != 5) {
      return;
    }

    auto& red_characters = world_context->red_characters;
    auto& blue_characters = world_context->blue_characters;

    for (int i = red_characters.size() - 1; i >= 0; i--) {
      int enemy_hq_location = world_context->location_count - 1;

      if (red_characters[i]->IsEscaped() &&
          red_characters[i]->location != enemy_hq_location) {
        Messenger::Send(red_characters[i]->name + " ran away");
        red_characters.erase(red_characters.begin() + i);
      }
    }

    for (int i = blue_characters.size() - 1; i >= 0; i--) {
      if (blue_characters[i]->IsEscaped() &&
          blue_characters[i]->location != 0) {
        Messenger::Send(blue_characters[i]->name + " ran away");
        blue_characters.erase(blue_characters.begin() + i);
      }
    }
  }

 private:
  std::shared_ptr<WorldContext> world_context;
};