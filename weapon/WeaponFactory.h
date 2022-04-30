#pragma once

#include <stdexcept>

#include "Weapon.h"

class WeaponFactory {
 public:
  static Weapon MakeSword() {
    return Weapon(kWeaponIdSword, 0.2);
  }

  static Weapon MakeBomb() {
    return Weapon(kWeaponIdBomb, 0.4, 0.5);
  }

  static Weapon MakeArrow() {
    return Weapon(kWeaponIdArrow, 0.3, 0.0, 2);
  }

  static Weapon Make(int id) {
    if (id == kWeaponIdSword) {
      return MakeSword();
    } else if (id == kWeaponIdBomb) {
      return MakeBomb();
    } else if (id == kWeaponIdArrow) {
      return MakeArrow();
    } else {
      throw std::invalid_argument("Invalid weapon id");
    }
  }
};
