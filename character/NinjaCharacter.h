#pragma once

#include "character/Character.h"

class NinjaCharacter : public Character {
 public:
  NinjaCharacter(std::string name, int id, int location);
  void Attack(Character& target, int weapon_index) override;
};