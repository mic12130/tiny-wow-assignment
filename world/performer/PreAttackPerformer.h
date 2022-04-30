#pragma once

#include "world/BattleOperator.h"
#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class PreAttackPerformer : public TimedEventHandleable {
 public:
  PreAttackPerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 != 35) {
      return;
    }

    for (auto& red : world_context->red_characters) {
      for (auto& blue : world_context->blue_characters) {
        if (red->location == blue->location) {
          BattleOperator::PerformPreAttack(*red, *blue);
        }
      }
    }
  }

 private:
  std::shared_ptr<WorldContext> world_context;
};