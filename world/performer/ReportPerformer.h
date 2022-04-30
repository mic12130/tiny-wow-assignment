#pragma once

#include "message/Messenger.h"
#include "world/BattleOperator.h"
#include "world/TimedEventHandleable.h"
#include "world/WorldContext.h"

class ReportPerformer : public TimedEventHandleable {
 public:
  ReportPerformer(std::shared_ptr<WorldContext> world_context)
      : world_context(world_context) {}

  void OnTimedEvent(int counter) override {
    if (counter % 60 == 50) {
      // Report headquarters

      Messenger::Send(GenerateMessage(world_context->red_hq));
      Messenger::Send(GenerateMessage(world_context->blue_hq));
    } else if (counter % 60 == 55) {
      // Report characters

      for (const auto& c : world_context->red_characters) {
        Messenger::Send(GenerateMessage(*c));
      }

      for (const auto& c : world_context->blue_characters) {
        Messenger::Send(GenerateMessage(*c));
      }
    }
  }

 private:
  std::string GenerateMessage(Character& c) const {
    int sword_count = 0;
    int bomb_count = 0;
    int arrow_count = 0;

    for (const auto& weapon : c.get_weapon_manager().get_weapons()) {
      if (weapon.id == kWeaponIdSword) {
        sword_count++;
      } else if (weapon.id == kWeaponIdBomb) {
        bomb_count++;
      } else if (weapon.id == kWeaponIdArrow) {
        arrow_count++;
      }
    }

    std::string weapon_message = std::to_string(sword_count) + " sword " +
                                 std::to_string(bomb_count) + " bomb " +
                                 std::to_string(arrow_count) + " arrow";
    std::string result = c.name + " has " + weapon_message +
                         " and " + std::to_string(c.health) + " elements";

    return result;
  }

  std::string GenerateMessage(Headquarter& hq) const {
    return std::to_string(hq.get_total_health()) + " elements in " + hq.get_name();
  }

  std::shared_ptr<WorldContext> world_context;
};