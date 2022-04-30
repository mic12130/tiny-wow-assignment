#pragma once

#include <memory>
#include <string>
#include <vector>

#include "weapon/Weapon.h"
#include "weapon/WeaponManager.h"

class Character {
 public:
  Character();
  virtual ~Character() = default;
  virtual void PreAttack(Character& target);
  virtual void Attack(Character& target, int weapon_index);
  virtual void Move(bool is_east);
  bool IsDead() const;
  bool IsEscaped() const;
  WeaponManager& get_weapon_manager();

  std::string name = "";
  int id = 0;
  int health = 100;
  int damage = 100;
  int loyalty = 100;
  int location = 0;

 protected:
  std::unique_ptr<WeaponManager> weapon_manager;
};