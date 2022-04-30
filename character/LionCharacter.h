#pragma once

#include "character/Character.h"

class LionCharacter : public Character {
 public:
  LionCharacter(std::string name, int id, int loyalty, int location);
  void Move(bool is_east) override;
};