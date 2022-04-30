#include "world/BattleOperator.h"

#include "weapon/Expelliarmus.h"

BattleResult BattleOperator::PerformAttack(
    Character& red,
    Character& blue,
    bool is_red_attack_first) {
  // Iterator of attack rounds
  // When it is odd, the red will perform an attack,
  // and when it is even, the blue will
  // Based on this mechanism, when is_red_attack_first is true,
  // we will set i's initial value to 1, so the blue will be
  // the first to attack in this case
  int i = is_red_attack_first ? 1 : 0;

  int red_weapon_used = 0;
  int blue_weapon_used = 0;
  bool red_health_unchanged = false;
  bool blue_health_unchanged = false;

  red.get_weapon_manager().Sort();
  blue.get_weapon_manager().Sort();

  while (true) {
    if (i % 2 == 0) {
      PerformSingleAttack(blue, red, blue_weapon_used, blue_health_unchanged);
    } else {
      PerformSingleAttack(red, blue, red_weapon_used, red_health_unchanged);
    }

    i++;

    // Breaks if both sides' health are stuck there
    if (blue_health_unchanged && red_health_unchanged) {
      break;
    }

    // Breaks if at least one was dead
    if (red.IsDead() || blue.IsDead()) {
      break;
    }
  }

  red.get_weapon_manager().RemoveInactivated();
  blue.get_weapon_manager().RemoveInactivated();

  // Calculate the result after all attacks terminated
  if (red.IsDead() == blue.IsDead()) {
    // This case includes situations of both dead and
    // both alive (but the battle is not able to continue)
    return BattleResult::Draw;
  }

  // If only one dead, transfers its weapons to the one alived
  if (red.IsDead()) {
    TransferWeapons(blue, red);
  } else if (blue.IsDead()) {
    TransferWeapons(red, blue);
  }

  return red.IsDead() ? BattleResult::BlueWin : BattleResult::RedWin;
}

void BattleOperator::PerformPreAttack(Character& red, Character& blue) {
  red.PreAttack(blue);
  blue.PreAttack(red);
}

void BattleOperator::TransferWeapons(Character& initiator, Character& enemy) {
  while (initiator.get_weapon_manager().count() < kMaxWeaponAllowed) {
    int targetWeaponIndex =
        Expelliarmus::GetTargetWeaponIndex(enemy.get_weapon_manager());

    if (targetWeaponIndex == kWeaponTransferNotAllowed) {
      break;
    }

    Expelliarmus::TransferWeapon(initiator.get_weapon_manager(),
                                 enemy.get_weapon_manager(),
                                 targetWeaponIndex);
  }
}

void BattleOperator::PerformSingleAttack(
    Character& initiator,
    Character& enemy,
    int& weapon_used,
    bool& health_unchanged) {
  int weapon_count = initiator.get_weapon_manager().count();

  if (weapon_count == 0) {
    health_unchanged = true;
    return;
  }

  int previous_health = initiator.health;
  initiator.Attack(enemy, weapon_used);
  weapon_used++;
  health_unchanged = previous_health == initiator.health;

  if (weapon_used == weapon_count) {
    initiator.get_weapon_manager().RemoveInactivated();
    weapon_used = 0;
  }
}