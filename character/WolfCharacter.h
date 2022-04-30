#pragma once

#include "character/Character.h"

class WolfCharacter : public Character {
 public:
  WolfCharacter(std::string name, int id, int location);
  void PreAttack(Character& target) override;
};