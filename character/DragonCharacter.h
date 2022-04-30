#pragma once

#include "character/Character.h"

class DragonCharacter : public Character {
 public:
  DragonCharacter(std::string name, int id, int location);
  void Attack(Character& target, int weapon_index) override;
};