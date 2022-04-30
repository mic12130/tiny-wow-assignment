#pragma once

#include <string>

enum WeaponId { kWeaponIdSword = 0,
                kWeaponIdBomb,
                kWeaponIdArrow };

struct Weapon {
  int id;
  double damage_ratio;
  double reflect_ratio;
  unsigned remaining_times;

  bool IsActivated() const {
    return remaining_times != 0;
  }

  std::string Name() const {
    if (id == kWeaponIdArrow) {
      return "arrow";
    } else if (id == kWeaponIdBomb) {
      return "bomb";
    } else if (id == kWeaponIdSword) {
      return "sword";
    }

    return "unknown weapon";
  }

  Weapon(int id, double damage_ratio, double reflect_ratio = 0.0,
         unsigned remaining_times = 1)
      : id(id),
        damage_ratio(damage_ratio),
        reflect_ratio(reflect_ratio),
        remaining_times(remaining_times) {}
};