#include "weapon/WeaponManager.h"

#include <stdexcept>

// Required by std::sort()
bool operator<(const Weapon& lhs, const Weapon& rhs) {
  if (lhs.id == rhs.id) {
    return lhs.remaining_times < rhs.remaining_times;
  }

  return lhs.id < rhs.id;
}

WeaponManager::WeaponManager() {
  weapons = {};
}

WeaponManager::WeaponManager(const std::vector<Weapon>& weapons)
    : weapons(weapons) {
  ThrowIfWeaponLimitExceed();
}

void WeaponManager::add_weapon(const Weapon& weapon) {
  weapons.push_back(weapon);
  ThrowIfWeaponLimitExceed();
}

void WeaponManager::remove_weapon(int index) {
  weapons.erase(weapons.begin() + index);
}

Weapon& WeaponManager::get_weapon(int index) {
  return weapons[index];
}

auto WeaponManager::get_weapons() const -> const std::vector<Weapon>& {
  return weapons;
}

size_t WeaponManager::count() const {
  return weapons.size();
}

void WeaponManager::Sort() {
  std::sort(weapons.begin(), weapons.end());
}

void WeaponManager::RemoveInactivated() {
  std::erase_if(weapons, [](const Weapon& w) {
    return w.IsActivated() == false;
  });
}

void WeaponManager::ThrowIfWeaponLimitExceed() {
  if (weapons.size() > kMaxWeaponAllowed) {
    throw std::runtime_error("Weapon limit exceed");
  }
}