#include "character/Character.h"

Character::Character() {
  weapon_manager = std::make_unique<WeaponManager>();
}

void Character::PreAttack(Character& target) {
}

void Character::Attack(Character& target, int weapon_index) {
  auto& weapon = weapon_manager->get_weapon(weapon_index);

  // Update target health
  int damage_delta = damage * weapon.damage_ratio;
  target.health -= damage_delta;

  // Update our health
  health -= int(damage_delta * weapon.reflect_ratio);

  // Update weapon remaining times
  weapon.remaining_times -= 1;
}

void Character::Move(bool is_east) {
  if (is_east) {
    location++;
  } else {
    location--;
  }
}

bool Character::IsDead() const {
  return health <= 0;
}

bool Character::IsEscaped() const {
  return loyalty <= 0;
}

WeaponManager& Character::get_weapon_manager() {
  return *weapon_manager;
}