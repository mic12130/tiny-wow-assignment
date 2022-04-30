#pragma once

#include "character/Character.h"

enum class BattleResult {
  RedWin,
  BlueWin,
  Draw
};

class BattleOperator {
 public:
  static BattleResult PerformAttack(
      Character& red,
      Character& blue,
      bool is_red_attack_first);
  static void PerformPreAttack(Character& red, Character& blue);

 private:
  static void TransferWeapons(Character& initiator, Character& enemy);
  static void PerformSingleAttack(
      Character& initiator,
      Character& enemy,
      int& weapon_used,
      bool& health_unchanged);
};