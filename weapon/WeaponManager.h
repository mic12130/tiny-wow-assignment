#pragma once

#include <vector>

#include "weapon/Weapon.h"

const size_t kMaxWeaponAllowed = 10;

class WeaponManager {
 public:
  WeaponManager();
  WeaponManager(const std::vector<Weapon>& weapons);

  // Add weapon and append it to the end
  void add_weapon(const Weapon& weapon);

  // Remove weapon at specific position
  void remove_weapon(int index);

  // Get weapon at specific position
  Weapon& get_weapon(int index);
  
  // Get all weapons
  auto get_weapons() const -> const std::vector<Weapon>&;

  size_t count() const;
  void Sort();
  void RemoveInactivated();

 private:
  void ThrowIfWeaponLimitExceed();

  std::vector<Weapon> weapons;
};