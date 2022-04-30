#pragma once

#include "message/Messenger.h"
#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class MovePerformer : public TimedEventHandleable {
 public:
  MovePerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 != 10) {
      return;
    }

    bool should_end = false;

    for (auto &c : world_context->red_characters) {
      c->Move(true);

      if (c->location != world_context->blue_hq.get_location()) {
        Messenger::Send(GenerateMarchMessage(*c));
      } else {
        Messenger::Send(GenerateOccupyMessage(*c, world_context->blue_hq));
        Messenger::Send(world_context->blue_hq.get_name() + " was taken");
        should_end = true;
      }
    }

    for (auto &c : world_context->blue_characters) {
      c->Move(false);

      if (c->location != world_context->red_hq.get_location()) {
        Messenger::Send(GenerateMarchMessage(*c));
      } else {
        Messenger::Send(GenerateOccupyMessage(*c, world_context->red_hq));
        Messenger::Send(world_context->red_hq.get_name() + " was taken");
        should_end = true;
      }
    }

    // We have to wait other move events to complete before we can end
    // the game, so validate should_end at the end of this func
    if (should_end) {
      world_context->set_ended();
    }
  }

 private:
  std::string GenerateMarchMessage(Character &c) const {
    return c.name + " marched to city " +
           std::to_string(c.location) + " with " +
           std::to_string(c.health) + " elements and force " +
           std::to_string(c.damage);
  }

  std::string GenerateOccupyMessage(Character &c, Headquarter &hq) const {
    return c.name + " reached " + hq.get_name() + " with " +
           std::to_string(c.health) + " elements and force " +
           std::to_string(c.damage);
  }

  std::shared_ptr<WorldContext> world_context;
};