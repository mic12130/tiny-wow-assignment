#pragma once

#include "weapon/WeaponManager.h"

const int kWeaponTransferNotAllowed = -1;

class Expelliarmus {
 public:
  // Get the index of weapon that has the highest
  // priority to be transferred
  // If the weapon manager does't own any weapon,
  // kWeaponTransferNotAllowed will be returned
  static int GetTargetWeaponIndex(WeaponManager& weapon_manager) {
    const auto& enemy_weapons = weapon_manager.get_weapons();

    if (enemy_weapons.size() == 0) {
      return kWeaponTransferNotAllowed;
    }

    int tmp_index = 0;
    int tmp_id = enemy_weapons[0].id;
    int tmp_remaining_times = enemy_weapons[0].remaining_times;

    for (int i = 0; i < enemy_weapons.size(); i++) {
      if (enemy_weapons[i].id < tmp_id &&
          enemy_weapons[i].remaining_times > tmp_remaining_times) {
        tmp_index = i;
        tmp_id = enemy_weapons[i].id;
        tmp_remaining_times = enemy_weapons[i].remaining_times;
      }
    }

    return tmp_index;
  }

  // Transferring specific weapon from the enemy to the initiator
  static void TransferWeapon(
      WeaponManager& initiator,
      WeaponManager& enemy,
      int weapon_index) {
    const auto& enemy_weapons = enemy.get_weapons();
    auto transfering_weapon = enemy_weapons[weapon_index];

    enemy.remove_weapon(weapon_index);
    initiator.add_weapon(transfering_weapon);
  }
};