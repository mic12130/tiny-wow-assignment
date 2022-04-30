#pragma once

#include "message/Messenger.h"
#include "world/BattleOperator.h"
#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class AttackPerformer : public TimedEventHandleable {
 public:
  AttackPerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 != 40) {
      return;
    }

    for (auto& blue : world_context->blue_characters) {
      for (auto& red : world_context->red_characters) {
        if (red->location == blue->location) {
          auto result = BattleOperator::PerformAttack(
              *red, *blue, red->location % 2 == 1);

          Messenger::Send(GenerateResultMessage(result, *red, *blue));
        }
      }
    }

    DeadCleanup(world_context->red_characters);
    DeadCleanup(world_context->blue_characters);
  }

 private:
  std::string GenerateResultMessage(
      BattleResult result,
      const Character& red, const Character& blue) const {
    // They are at same location, so we can take anyone's
    std::string location_str = std::to_string(red.location);
    std::string msg;

    if (result == BattleResult::Draw) {
      // Check both daed or both alive
      if (red.IsDead()) {
        msg = "both " + red.name + " and " + blue.name +
              " died in city " + location_str;
      } else {
        msg = "both " + red.name + " and " + blue.name +
              " were alive in city " + location_str;
      }
    } else if (result == BattleResult::RedWin) {
      msg = red.name + " killed " + blue.name +
            " in city " + location_str +
            " remaining " + std::to_string(red.health) +
            " elements";
    } else if (result == BattleResult::BlueWin) {
      msg = blue.name + " killed " + red.name +
            " in city " + location_str +
            " remaining " + std::to_string(blue.health) +
            " elements";
    }

    return msg;
  }

  void DeadCleanup(std::vector<std::shared_ptr<Character>>& characters) {
    std::erase_if(characters, [](const std::shared_ptr<Character>& c) {
      return c->IsDead();
    });
  }

  std::shared_ptr<WorldContext> world_context;
};